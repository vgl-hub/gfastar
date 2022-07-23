#include <main.h>

std::string version = "0.1";

int cmd_flag;

int main(int argc, char **argv) {
    
    short int c; // optarg
    short unsigned int pos_op = 1; // optional arguments
    
    bool arguments = true;
    
    std::string cmd;
    
    if (argc == 1) { // gfastats with no arguments
            
        printf("gfastar [command]\n-h for additional help.\n");
        exit(0);
        
    }
    
    static struct option long_options[] = { // struct mapping long options
        {"cmd", no_argument, &cmd_flag, 1},
        {"version", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        
        {0, 0, 0, 0}
    };
    
    const static std::unordered_map<std::string,int> tools{
        {"stats",1}
        {"align",2}
    };
    
    while (arguments) { // loop through argv
        
        int option_index = 0;
        
        c = getopt_long(argc, argv, "-:vh",
                        long_options, &option_index);
        
        if (c == -1) { // exit the loop if run out of options
            break;
            
        }

        switch (c) {
            case ':': // handle options without arguments
                switch (optopt) { // the command line option last matched
                    case 'b':
                        break;
                        
                    default:
                        fprintf(stderr, "option -%c is missing a required argument\n", optopt);
                        return EXIT_FAILURE;
                }
                break;
            default: // handle positional arguments
                                
                switch (tools.count(optarg) ? tools.at(optarg) : 0) {
                    case 1:
                        cmd = "gfastats/build/bin/gfastats" + getArgs(optarg, argc, argv);;
                        
                        arguments = false;
                        
                        break;
                    case 2:
                        cmd = "gfalign/build/bin/gfalign" + getArgs(optarg, argc, argv);;
                        
                        arguments = false;
                        
                        break;
                        
                }
                
            case 0: // case for long options without short options
                
//                if (strcmp(long_options[option_index].name,"line-length") == 0)
//                  splitLength = atoi(optarg);
                
                break;
                
            case 'v': // software version
                printf("gfastar v%s\n", version.c_str());
                printf("Giulio Formenti giulio.formenti@gmail.com\n");
                exit(0);
                
            case 'h': // help
                printf("gfastar [command]\n");
                printf("\nOptions:\n");
                printf("-v --version software version.\n");
                printf("--cmd print $0 to stdout.\n");
                exit(0);
        }
        
        if    (argc == 2 || // handle various cases in which the output should include summary stats
              (argc == 3 && pos_op == 2) ||
              (argc == 4 && pos_op == 3)) {
            
        }
        
    }
    
    if (cmd_flag) { // print command line
        for (unsigned short int arg_counter = 0; arg_counter < argc; arg_counter++) {
            printf("%s ", argv[arg_counter]);
        }
        printf("\n");
        
    }
    
    std::cout<<"Invoking: "<<cmd<<std::endl;
    std::system(cmd.c_str());
    
    exit(EXIT_SUCCESS);
    
}

std::string getArgs(char* optarg, unsigned int argc, char **argv) {
    
    std::string cmd;
    bool record = false;

    for (unsigned short int arg_counter = 0; arg_counter < argc; arg_counter++) {
        
        if (optarg != argv[arg_counter] && !record) {
            continue;
        }else{
            record = true;
            if(optarg != argv[arg_counter]){
                cmd += ' ';
                cmd += argv[arg_counter];
            }
        }
    }
    
    return cmd;
    
}
