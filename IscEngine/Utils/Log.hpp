#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

namespace IscEngine {

	// Logs data to console and file
	class Log {

		private:

			std::string logFilename;

		public:
			
			// New definition of "cout"
			static Log cout;
			
			//////////////////////////////////////////////////////////////////////////////////////////////

			// Creates the Log, deletes the file content and writes the current time
			Log(std::string fileName) {

				logFilename = fileName;
				std::ofstream outFile;
				outFile.open(logFilename, std::ios::trunc);
				const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
				outFile << std::ctime(&time);
				outFile << "------------------------" << std::endl;
				outFile.close();

			}

			// << operator overload (data)
			template <typename T> Log& operator << (const T& t) {

				std::cout << t;
				std::ofstream outFile;
				outFile.open(logFilename, std::ios::app);
				outFile << t;
				outFile.close();

				return *this;

			}

			// << operator overload (function, adds support for std::endl)
			Log& operator << (std::ostream&(*f)(std::ostream&)) {

				std::cout << f;
				std::ofstream outFile;
				outFile.open(logFilename, std::ios::app);
				outFile << f;
				outFile.close();

				return *this;

			}

	};

}