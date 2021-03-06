/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

   File:       ExternalDataSource.h

   Author:     Andreas Schwab <schwab@suse.de>
   Maintainer: Thomas Roelz <tom@suse.de>

/-*/

#ifndef ExternalDataSource_h
#define ExternalDataSource_h

#include <stdio.h>

#include <string>

/**
 * @short Bidirectional stream to external data
 */
class ExternalDataSource
{
protected:
    FILE *inputfile;
    FILE *outputfile;

private:
    char *linebuffer;
    size_t linebuffer_size;

public:
    /**
     * Create a new instance.
     * @param inputfile The stream for reading
     * @param outputfile The stream for writing
     * Either can be NULL if no reading/writing is allowed.
     */
    ExternalDataSource(FILE *inputfile = 0, FILE *outputfile = 0);

    /**
     * Implicitly close the connection.
     */
    virtual ~ExternalDataSource();

    /**
     * Send some data to the output stream.
     * @param buffer The data to send
     * @param length The size of it
     */
    bool send (const char *buffer, size_t length);

    /**
     * Send some data down the stream.
     * @param string The data to send
     */
    bool send (std::string s);

    /**
     * Read some data from the input stream.
     * @param buffer Where to put the data
     * @param length How much to read at most
     * Returns the amount actually received
     */
    size_t receive(char *buffer, size_t length);

    /**
     * Read one line from the input stream.
     * Returns the line read, including the terminator.
     */
    std::string receiveLine();

    /**
     * Read characters into a string until character c is
     * read. C is put at the end of the string.
     */
    std::string receiveUpto(char c);
    /**
     * Set the blocking mode of the input stream.
     * @param mode True if the reader should be blocked waiting for input.
     * This is the initial default.
     */
    void setBlocking(bool mode);

    /**
     * Close the input and output streams.
     */
    virtual int close();

    /**
     * Return the input stream.
     */
    FILE *inputFile() const  { return inputfile; }

    /**
     * Return the output stream.
     */
    FILE *outputFile() const { return outputfile; }
};


#endif // ExternalDataSource_h

