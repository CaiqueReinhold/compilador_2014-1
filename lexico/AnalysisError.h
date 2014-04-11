#ifndef ANALYSIS_ERROR_H
#define ANALYSIS_ERROR_H

class AnalysisError
{
public:

    AnalysisError(const char* msg, int position, int line)
      : message(msg), position(position), line(line) { }

    const char* getMessage() const { return message; }
    int getPosition() const { return position; }
    int getLine() const { return line; }

private:
    const char* message;
    int position;
    int line;
};

#endif
