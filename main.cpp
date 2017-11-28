#include <iostream>
#include <fstream>
#include <random>

int main(int argc, char *argv[])
{
    
    std::string input_filename;
    std::string output_filename;
    
    for(int ix{1}; ix < argc; ++ ix)
    {
        std::string current_arg{argv[ix]};
        const std::string arg_input_filename("--input");
        const std::string arg_output_filename("--output");
        
        if(current_arg == arg_input_filename)
        {
            if(++ ix < argc)
            {
                input_filename = std::string(argv[ix]);
            }
            else
            {
                std::cerr << "Error: Expected string after argument " << current_arg << std::endl;
            }
        }
        else if(current_arg == arg_output_filename)
        {
            if(++ ix < argc)
            {
                output_filename = std::string(argv[ix]);
            }
            else
            {
                std::cerr << "Error: Expected string after argument " << current_arg << std::endl;
            }
        }
        else
        {
            std::cerr << "Argument " << current_arg << " not recognized" << std::endl;
        }
    }
    
    if(input_filename.size() > 0)
    {
        std::ifstream ifile(input_filename.c_str(), std::ios::ate);
        if(ifile.is_open())
        {
            std::streampos input_file_size{ifile.tellg()};
            //char *buffer = new char[static_cast<std::size_t>(input_file_size) + 1];
            //buffer[input_file_size] = 0;
            char *buffer = new char[input_file_size];
            ifile.seekg(0, std::ios::beg);
            ifile.read(buffer, input_file_size);
            
            //std::cout << buffer << std::endl;
            
            std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_int_distribution<> dis(0, 1);
            //bool a1{false};
            //bool a2{a1};
            bool swap{false};
            const char diff{'a' - 'A'};
            
            for(std::size_t i{0}; i < static_cast<std::size_t>(input_file_size); ++ i)
            {
                char c{buffer[i]};
                if(dis(gen) == 0)
                {
                    swap = true;
                }
                else
                {
                    swap = false;
                }
                
                // A - Z
                if(('A' <= c) && (c <= 'Z'))
                {
                    if(swap)
                    {
                        c += diff;
                    }
                }
                // a - z
                else if(('a' <= c) && (c <= 'z'))
                {
                    if(swap)
                    {
                        c -= diff;
                    }
                }
                else if(' ' == c ||
                        ',' == c ||
                        '.' == c ||
                        '?' == c ||
                        '\'' == c ||
                        '\\' == c || '/' == c ||
                        '(' == c ||  ')' == c ||
                        '%' == c ||
                        '\n' == c ||
                        '!' == c ||
                        '@' == c ||
                        '#' == c ||
                        '$' == c ||
                        '^' == c ||
                        '&' == c ||
                        '*' == c ||
                        '{' == c || '}' == c ||
                        '[' == c || ']' == c ||
                        '`' == c ||
                        '\t' == c ||
                        '-' == c || '+' == c || '=' == c ||
                        '_' == c ||
                        ':' == c || ';' == c ||
                        '<' == c || '>' == c ||
                        '|' == c)
                {
                
                }
                else if(('0' <= c) && (c <= '9'))
                {
                
                }
                else
                {
                    std::cerr << "Unrecognized character @ " << i << " : " << c << ", " << (int)c << " (int)" << std::endl;
                }
                
                buffer[i] = c;
            }
            
            if(output_filename.size() == 0)
            {
                std::cout.write(buffer, input_file_size); std::cout << std::endl;
            }
            else
            {
                std::ofstream ofile(output_filename.c_str());
                if(ofile.is_open())
                {
                    ofile.write(buffer, input_file_size);
                    std::cout << "Output written to " << output_filename << std::endl;
                }
                else
                {
                    std::cerr << "Error: Could not open file " << output_filename << " for write" << std::endl;
                }
            }
        }
        else
        {
            std::cerr << "Error: Could not open file " << input_filename << " for read" << std::endl;
            return 2;
        }
    }
    else
    {
        std::cerr << "Error: No --input argument provided" << std::endl;
        return 1;
    }
    
    return 0;

}
