void ReadFile(const std::string &path){
    std::ifstream input("input.txt");
    std::string line;
    while (getline(input, line)){
        std::cout<<line<<std::endl;
    }
}