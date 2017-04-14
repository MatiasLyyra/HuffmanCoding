#ifndef HUFFMANCODING_TIMERESULTS_H
#define HUFFMANCODING_TIMERESULTS_H
using time_type_t = long long int;

struct EncodingResult
{
    EncodingResult()
            : fileReading{0},
              huffmanTreeBuilding{0},
              encoding{0},
              headerWrite{0},
              encodedDataWrite{0},
              total{0},
              success{false}
    {}
    time_type_t fileReading = 0;
    time_type_t huffmanTreeBuilding = 0;
    time_type_t encoding = 0;
    time_type_t headerWrite = 0;
    time_type_t encodedDataWrite = 0;
    time_type_t total = 0;
    bool success = false;
};


struct DecodingResults
{
    DecodingResults()
            : fileHeaderRead{0},
              fileDataRead{0},
              decoding{0},
              fileWrite{0},
              total{0},
              success{false}
    {}
    time_type_t fileHeaderRead;
    time_type_t fileDataRead;
    time_type_t decoding;
    time_type_t fileWrite;
    time_type_t total;
    bool success;
};

#endif //HUFFMANCODING_TIMERESULTS_H
