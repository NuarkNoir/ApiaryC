#pragma once

/**
 * @brief Simply initializes the name member to the name of the project
 */
struct library {
  const char* name;
};

/**
 * @brief Creates an instance of library with the name of the project
 */
struct library create_library(void);
