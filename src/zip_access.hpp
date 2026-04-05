
#include <zip.h>
#include <string>
#include <format>
#include <stdexcept>
#include <vector>
#include <memory>

namespace zip_access
{
    std::string get_zip_strerror(int err)
    {
        zip_error_t zerr;
        zip_error_init_with_code(&zerr, err);
        std::string zip_msg(zip_error_strerror(&zerr));

        zip_error_fini(&zerr);
        return zip_msg;
    }


    std::string get_zip_strerror(const std::string& msg, int err)
    {
        return msg + get_zip_strerror(err);
    }


    std::string get_zip_strerror(const std::string& msg, zip& archive)
    {
        int err = zip_error_code_zip(zip_get_error(&archive));
        return msg + get_zip_strerror(err);
    }


    class ZipException : public std::runtime_error
    {
    public:
        ZipException(const std::string& msg, int err)
        : std::runtime_error(get_zip_strerror(msg, err))
        {}

        ZipException(const std::string& msg, zip& archive)
        : std::runtime_error(get_zip_strerror(msg, archive))
        {}
    };


    class ZipRAII
    {
    private:
        zip* _zip = NULL;

    public:

        ZipRAII(const std::string& zip_path)
        {
            int err;
            _zip = zip_open(zip_path.c_str(), 0, &err);

            if (!_zip)
                throw ZipException(std::format("Failed to open: {}.", zip_path), err);
        }

        ~ZipRAII()
        {
            if (_zip != NULL)
                zip_close(_zip);
        }

        zip& getHandler()
        {
            return *_zip;
        }
    };

    bool zip_name_located(zip& archive, const std::string& path, int* idx)
    {
        int res = zip_name_locate(&archive, path.c_str(), ZIP_FL_ENC_GUESS);

        if (res < 0 )
            return false;

        *idx = res;
        return true;
    }

    std::vector<uint8_t> read_file(zip& archive, const std::string& path)
    {
        zip_stat_t stat;
        zip_stat_init(&stat);  // always initialize first!

        if (zip_stat(&archive, path.c_str(), ZIP_FL_ENC_GUESS, &stat) != 0)
            throw ZipException(std::format("zip_stat failed: {}.", path), archive);

        // MUST check valid flags before trusting stat fields
        if (!(stat.valid & ZIP_STAT_SIZE))
            throw std::runtime_error(std::format("zip_stat size not valid: {}.", path));

        zip_file_t* file = zip_fopen(&archive, path.c_str(), ZIP_FL_ENC_GUESS);

        if (!file)
            throw ZipException(std::format("zip_fopen failed: {}.", path), archive);

        std::vector<uint8_t> buffer(stat.size);
        zip_int64_t bytes_read = zip_fread(file, buffer.data(), stat.size);
        zip_fclose(file);

        if (bytes_read != static_cast<zip_int64_t>(stat.size))
            throw std::runtime_error(std::format("zip_fread incomplete: {}.", path));

        return buffer;
    }

    int get_num_entries(zip& archive)
    {
        return (int)zip_get_num_entries(&archive,  ZIP_FL_UNCHANGED);
    }

    std::string get_name(zip& archive, int i)
    {
        auto name = zip_get_name(&archive, i, ZIP_FL_ENC_GUESS);

        if (name == NULL)
            throw ZipException(std::format("zip_get_name failed with index: {}.", i).c_str(), archive);

        return name;
    }

    std::unique_ptr<std::vector<std::string>> get_file_paths(zip& archive)
    {
        auto paths = std::make_unique<std::vector<std::string>>();
        int n = get_num_entries(archive);

        for (int i = 0; i < n; ++i)
            paths->push_back(get_name(archive, i));

        return paths;
    }
};
