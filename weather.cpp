#include <iostream>
#include <string>
#include <curl/curl.h>


using namespace std;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s) {
    size_t newLength = size*nmemb;
    size_t oldLength = s->size();
    try {
        s->resize(oldLength + newLength);
    } catch(std::bad_alloc &e) {
        return 0;
    }

    std::copy((char*)contents,(char*)contents+newLength,s->begin()+oldLength);
    return size*nmemb;
}
void prettyOutput(string s)
{
    const string green = "\033[1;32m";

    const string reset = "\033[0m";
    const string yellow = "\033[1;33m";
    const string blink = "\033[5m";
    cout << green << string(sizeof(s)+10, '=') << reset << endl;
    cout << blink << yellow << s << reset << endl;
    cout << green << string(sizeof(s)+10, '=') << reset << endl;
}
string getWeather()
{
    string weather;
    CURL *curl;
    CURLcode res;
    string url = "https://wttr.in/?format=%l:+%C+%t+%w";
    curl = curl_easy_init();
    if(curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &weather);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return weather;
}

int main() 
{
    string result = getWeather();
    prettyOutput(result);
    delete &result;
    result = nullptr;
    return 0;
}
