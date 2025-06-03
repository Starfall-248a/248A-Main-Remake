#pragma once

#include "lemlib/asset.hpp"
#include <string>
#include <vector>

namespace lemlib_tarball {

/**
 * @brief Decoder class for parsing and accessing paths from a "LemLib Tarball" file.
 *
 * A "LemLib Tarball" file is a file that contains the data of multiple paths.
 * To create a "LemLib Tarball" file, go to https://path.jerryio.com and select "LemLib Tarball" format.
 * Read documentation for more information: https://docs.path.jerryio.com/docs/formats/LemLibTarballFormatV0_5
 *
 * To use this class, you need to first import the "LemLib Tarball" file as an asset using the ASSET macro.
 * After that, pass the asset to the Decoder constructor.
 * The Decoder will then be able to access the contents of the file and decode it into a list of paths.
 *
 * @example
 * // You only need to import the "LemLib Tarball" file once
 * ASSET(my_lemlib_tarball_file);
 *
 * // Create a Decoder to decode the tarball file
 * lemlib_tarball::Decoder decoder(my_lemlib_tarball_file);
 *
 * // You can now access the paths by their name.
 * // Use [] to access the paths by their name
 * chassis.follow(decoder["Path 1"], 15, 2000);
 * chassis.follow(decoder["Path 2"], 15, 2000);
 */
class Decoder {
    protected:
        /** @brief List of path names extracted from the tarball */
        std::vector<std::string> paths;
        /** @brief List of asset data corresponding to each path */
        std::vector<asset> assets;
    public:
        /**
         * @brief Constructs a Decoder with the given tarball asset.
         * @param tarball The tarball asset containing path data.
         */
        Decoder(const asset& tarball);

        /**
         * @brief Checks if a given path name exists in the tarball.
         * @param path_name The name of the path to check.
         * @return True if the path exists, false otherwise.
         */
        bool has(const char* path_name);

        /**
         * @brief Retrieves the asset associated with a given path name.
         * @param path_name The name of the path.
         * @return Reference to the asset corresponding to the path.
         */
        asset& get(const char* path_name);

        /**
         * @brief Overloads the subscript operator to access assets by path name.
         * @param path_name The name of the path.
         * @return Reference to the asset corresponding to the path.
         */
        asset& operator[](const char* path_name);
};

} // namespace lemlib_tarball