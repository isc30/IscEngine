#pragma once

#include <iostream>
#include <fstream> // Files
#include <chrono>
#include <ctime>

namespace IscEngine {

	class Log {

		private:

		std::string logFilename;

		public:

		static Log cout;

		Log(std::string fileName) {

			logFilename = fileName;
			std::ofstream outFile;
			outFile.open(logFilename, std::ios::trunc);
			const auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			outFile << std::ctime(&time);
			outFile << "------------------------" << std::endl;
			outFile.close();

		}

		template <typename T>
		Log& operator << (const T& t) {

			std::cout << t;
			std::ofstream outFile;
			outFile.open(logFilename, std::ios::app);
			outFile << t;
			outFile.close();

			return *this;

		}

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