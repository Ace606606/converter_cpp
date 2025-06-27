// ./include/logging.hpp
#pragma once

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define TIME __DATE__ " " __TIME__ " "
#define SCOPE __FILE__ ":" TOSTRING(__LINE__)
#define LOGINFO TIME "[INFO] "
#define LOGERROR TIME SCOPE " [ERROR] "