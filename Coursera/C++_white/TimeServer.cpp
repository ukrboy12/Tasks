//
// Created by MavkaWork on 7/2/2021.
//

class TimeServer {
public:
    std::string GetCurrentTime(){
        try {
            last_fetched_time = AskTimeServer();
            return last_fetched_time;
        } catch (system_error& e){
            return last_fetched_time;
        } catch (...){
            throw;
        }
    }
private:
    std::string last_fetched_time = "00:00:00";
};