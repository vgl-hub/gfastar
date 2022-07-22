#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <unordered_map>

#include <getopt.h>

std::string getArgs(char* optarg, unsigned int argc, char **argv);

#endif /* MAIN_H */
