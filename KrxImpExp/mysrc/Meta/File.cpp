///////////////////////////////////////////////////////////////////////////////
// Name:        File.cpp
// Purpose:     Definition of TFile class.
// Author:      Vitaly Baranov
// Created:     January 14, 2009
// Modified by:  
// Licence:     GNU General Public License
///////////////////////////////////////////////////////////////////////////////

#ifndef FILE_CPP
#define FILE_CPP

// Error messages
#define ErrFileNotCreated	_T("Could not open file for write.\nFile path: \"%1\".")
#define ErrFileNotFound		_T("Could not open file for read.\nFile path: \"%1\".")
#define ErrSeekOutOfFile	_T("Attempt to seek file pointer out of file.\nFile path: \"%1\".\nPosition of file pointer: %2.\nAllowable range: %3..%4.")
#define ErrWriteFailed		_T("Could not write data to file.\nFile path: \"%1\".\nSize of data: %2.")
#define ErrIntOutOfRange	_T("Could not write an integer to file.\nAn integer is out of range.\nFile path: \"%1\".\nInteger: %2.\nAllowable range: %3..%4.")
#define ErrReadFailed		_T("Could not read data from file.\nFile path: \"%1\".\nPosition in file: %2.\nSize of data: %3.")
#define ErrStringTooLong	_T("Could not read a null-terminated string from file.\nThe string seems to be too long.\nFile path: \"%1\".\nPosition in file: %2.")
#define ErrLineTooLong		_T("Could not read a CR+LF ended line from file.\nThe line seems to be too long.\nFile path: \"%1\".\nPosition in file: %2.")

#include "FormatMsg.cpp"

// Special class for operations on opened file
CLASS(TFile)

// Private section:
private:

	FILE*	__stream;
	TSTRING	__name;
	TSTRING	__mode;
	int __size;
	int __pos;

	void __MoveFilePos(FC<int>::ArgType ofs)
	{
		this->__pos = this->__pos + ofs;
		if (this->__size < this->__pos)
		{
			this->__size = this->__pos;		// TODO: find stl equivalent to this 'if'
		}
	}

// Public section:
public:

	// Initialize
	void Init()
	{
		this->__stream = INVALID_STREAM;
		this->__name = EMPTY_STRING;
		this->__mode = EMPTY_STRING;
		this->__size = 0;
		this->__pos = 0;
	}

	// Opens a file for reading or writing base on the openMode parameter.
	// This can either be "wb" for writing binary file,
	// "rb" for reading binary file, "wt" for writing text file,
	// "rt" for reading text file.
	// This function throws exception if it cannot open file.

	void Open(TSTRING filename, TSTRING mode)
	{
		if (this->__stream != INVALID_STREAM)
		{
			this->Close();
		}

		int filesz = GetFlSize(filename);
		this->__stream = OPEN_FILE(filename, mode);

		if (this->__stream == INVALID_STREAM)
		{
			if (mode.find(T("w")) != std::string::npos)
			{
				throw(FormatMsg1(ErrFileNotCreated, filename));
			}
			else
			{
				throw(FormatMsg1(ErrFileNotFound, filename));
			}
		}

		this->__name = filename;
		this->__mode = mode;
		this->__size = filesz;
		this->__pos = 0;
	}

	// Returns TRUE if the file is opened or FALSE elsewise.
	bool IsOpened()
	{
		return this->__stream != INVALID_STREAM;
	}

	// Closes the file if it was opened
	void Close()
	{
		if (this->__stream != INVALID_STREAM)
		{
			CloseFl(this->__stream);
			this->Init();
		}
	}

	// Gets the file's name with full path.
	// This function required the file to be opened.
	TSTRING& GetName()
	{
		return this->__name;
	}

	// Gets the file's open mode.
	// This is the same mode as was specified when the file was opened.
	TSTRING GetMode()
	{
		return this->__mode;
	}

	// Get the file's size.
	// This function required the file to be opened.
	int GetSize()
	{
		return this->__size;
	}

	// Gets the position of the file pointer.
	// This function required the file to be opened.
	int GetPos()
	{
		return this->__pos;
	}

	// Moves the file pointer to a specified position.
	// This function throws exception if the specified position is after the file's end.

MEMBER_PROC_1(SetPos, TINT, pos)
	IF(pos != SELF __pos)
		IF(pos < 0 OR pos > SELF __size)
			THROW(CALLF5(FormatMsg4, ErrSeekOutOfFile, SELF __name, HEXFORM(pos), HEXFORM(0), HEXFORM(SELF __size)))
		END_IF
		FILE_SEEK(SELF __stream, pos)
		ASSIGN(SELF __pos, pos)
	END_IF
END_MEMBER_PROC

// Tests for end of file
MEMBER_FUNC_0(TBOOL, Eof)
	RETURN_VAL(SELF __pos == SELF __size)
END_MEMBER_FUNC

// Writes 1-byte signed integer to binary file.
// This function throws exception if a error appears.
MEMBER_PROC_1(WriteSignedChar, TINT, i)
	IF(i < -128 OR i > 127)
		THROW(CALLF5(FormatMsg4, ErrIntOutOfRange, SELF __name, INT_TO_STRING(i), T("-128"), T("127")))
	END_IF
	LOCAL_VAR(TBOOL, b, WRITE_SIGNED_CHAR(SELF __stream, i))
	IF(NOT(b))
		THROW(CALLF3(FormatMsg2, ErrWriteFailed, SELF __name, T("1")))
	END_IF
	CALLP1(SELF __MoveFilePos, 1)
END_MEMBER_PROC

// Writes 1-byte unsigned integer to binary file.
// This function throws exception if a error appears.
MEMBER_PROC_1(WriteUnsignedChar, TINT, i)
	IF(i < 0 OR i > 255)
		THROW(CALLF5(FormatMsg4, ErrIntOutOfRange, SELF __name, INT_TO_STRING(i), T("0"), T("255")))
	END_IF
	LOCAL_VAR(TBOOL, b, WRITE_UNSIGNED_CHAR(SELF __stream, i))
	IF(NOT(b))
		THROW(CALLF3(FormatMsg2, ErrWriteFailed, SELF __name, T("1")))
	END_IF
	CALLP1(SELF __MoveFilePos, 1)
END_MEMBER_PROC

// Writes 1-byte boolean to binary file.
// This function throws exception if a error appears.
MEMBER_PROC_1(WriteBool, TBOOL, b)
	LOCAL_VAR(TINT, i, 0)
	IF(b)
		ASSIGN(i, 1)
	END_IF
	CALLP1(SELF WriteUnsignedChar, i)
END_MEMBER_PROC

// Writes 2-byte signed integer to binary file.
// This function throws exception if a error appears.
MEMBER_PROC_1(WriteSignedShort, TINT, i)
	IF(i < -32768 OR i > 32767)
		THROW(CALLF5(FormatMsg4, ErrIntOutOfRange, SELF __name, INT_TO_STRING(i), T("-32768"), T("32767")))
	END_IF
	LOCAL_VAR(TBOOL, b, WRITE_SIGNED_SHORT(SELF __stream, i))
	IF(NOT(b))
		THROW(CALLF3(FormatMsg2, ErrWriteFailed, SELF __name, T("2")))
	END_IF
	CALLP1(SELF __MoveFilePos, 2)
END_MEMBER_PROC

// Writes 2-byte unsigned integer to binary file.
// This function throws exception if a error appears.
MEMBER_PROC_1(WriteUnsignedShort, TINT, i)
	IF(i < 0 OR i > 65535)
		THROW(CALLF5(FormatMsg4, ErrIntOutOfRange, SELF __name, INT_TO_STRING(i), T("0"), T("65535")))
	END_IF
	LOCAL_VAR(TBOOL, b, WRITE_UNSIGNED_SHORT(SELF __stream, i))
	IF(NOT(b))
		THROW(CALLF3(FormatMsg2, ErrWriteFailed, SELF __name, T("2")))
	END_IF
	CALLP1(SELF __MoveFilePos, 2)
END_MEMBER_PROC

// Writes 4-byte signed integer to binary file.
// This function throws exception if a error appears.
MEMBER_PROC_1(WriteSignedLong, TINT, i)
	LOCAL_VAR(TBOOL, b, WRITE_SIGNED_LONG(SELF __stream, i))
	IF(NOT(b))
		THROW(CALLF3(FormatMsg2, ErrWriteFailed, SELF __name, T("4")))
	END_IF
	CALLP1(SELF __MoveFilePos, 4)
END_MEMBER_PROC

// Writes 4-byte unsigned integer to binary file.
// This function throws exception if a error appears.
MEMBER_PROC_1(WriteUnsignedLong, TINT, i)
	LOCAL_VAR(TBOOL, b, WRITE_UNSIGNED_LONG(SELF __stream, i))
	IF(NOT(b))
		THROW(CALLF3(FormatMsg2, ErrWriteFailed, SELF __name, T("4")))
	END_IF
	CALLP1(SELF __MoveFilePos, 4)
END_MEMBER_PROC

// Writes 4-byte floating point number to binary file.
// This function throws exception if a error appears.
MEMBER_PROC_1(WriteFloat, TFLOAT, f)
	LOCAL_VAR(TBOOL, b, WRITE_FLOAT(SELF __stream, f))
	IF(NOT(b))
		THROW(CALLF3(FormatMsg2, ErrWriteFailed, SELF __name, T("4")))
	END_IF
	CALLP1(SELF __MoveFilePos, 4)
END_MEMBER_PROC

// Writes a null-terminated string to binary file.
// The terminated zero is also written.
// This function throws exception if a error appears.
MEMBER_PROC_1(WriteString, TSTRING, str)
	LOCAL_VAR(TBOOL, b, WRITE_STRING(SELF __stream, str))
	LOCAL_VAR(TINT, sz, STRLEN(str) + 1)
	IF(NOT(b))
		THROW(CALLF3(FormatMsg2, ErrWriteFailed, SELF __name, INT_TO_STRING(sz)))
	END_IF
	CALLP1(SELF __MoveFilePos, sz)
END_MEMBER_PROC

// Writes a line to text file. CR+LF are also written.
// This function throws exception if a error appears.
MEMBER_PROC_1(WriteLine, TSTRING, str)
	LOCAL_VAR(TBOOL, b, WRITE_LINE(SELF __stream, str))
	LOCAL_VAR(TINT, sz, STRLEN(str) + 2)
	IF(NOT(b))
		THROW(CALLF3(FormatMsg2, ErrWriteFailed, SELF __name, INT_TO_STRING(sz)))
	END_IF
	CALLP1(SELF __MoveFilePos, sz)
END_MEMBER_PROC

// Reads 1-byte signed integer from binary file.
// This function throws exception if a error appears.
MEMBER_FUNC_0(TINT, ReadSignedChar)
	LOCAL_VAR(TINT, i, READ_SIGNED_CHAR(SELF __stream))
	IF(i == INVALID_INT)
		THROW(CALLF4(FormatMsg3, ErrReadFailed, SELF __name, HEXFORM(SELF __pos), T("1")))
	END_IF
	CALLP1(SELF __MoveFilePos, 1)
	RETURN_VAL(i)
END_MEMBER_PROC

// Reads 1-byte unsigned integer from binary file.
// This function throws exception if a error appears.
MEMBER_FUNC_0(TINT, ReadUnsignedChar)
	LOCAL_VAR(TINT, i, READ_UNSIGNED_CHAR(SELF __stream))
	IF(i == INVALID_INT)
		THROW(CALLF4(FormatMsg3, ErrReadFailed, SELF __name, HEXFORM(SELF __pos), T("1")))
	END_IF
	CALLP1(SELF __MoveFilePos, 1)
	RETURN_VAL(i)
END_MEMBER_PROC

// Reads 1-byte boolean from binary file.
// This function throws exception if a error appears.
MEMBER_FUNC_0(TBOOL, ReadBool)
	LOCAL_VAR(TINT, i, CALLF0(SELF ReadUnsignedChar))
	RETURN_VAL(i != 0)
END_MEMBER_PROC

// Reads 2-byte signed integer from binary file.
// This function throws exception if a error appears.
MEMBER_FUNC_0(TINT, ReadSignedShort)
	LOCAL_VAR(TINT, i, READ_SIGNED_SHORT(SELF __stream))
	IF(i == INVALID_INT)
		THROW(CALLF4(FormatMsg3, ErrReadFailed, SELF __name, HEXFORM(SELF __pos), T("2")))
	END_IF
	CALLP1(SELF __MoveFilePos, 2)
	RETURN_VAL(i)
END_MEMBER_PROC

// Reads 2-byte unsigned integer from binary file.
// This function throws exception if a error appears.
MEMBER_FUNC_0(TINT, ReadUnsignedShort)
	LOCAL_VAR(TINT, i, READ_UNSIGNED_SHORT(SELF __stream))
	IF(i == INVALID_INT)
		THROW(CALLF4(FormatMsg3, ErrReadFailed, SELF __name, HEXFORM(SELF __pos), T("2")))
	END_IF
	CALLP1(SELF __MoveFilePos, 2)
	RETURN_VAL(i)
END_MEMBER_PROC

// Reads 4-byte signed integer from binary file.
// This function throws exception if a error appears.
MEMBER_FUNC_0(TINT, ReadSignedLong)
	LOCAL_VAR(TINT, i, READ_SIGNED_LONG(SELF __stream))
	IF(i == INVALID_INT)
		THROW(CALLF4(FormatMsg3, ErrReadFailed, SELF __name, HEXFORM(SELF __pos), T("4")))
	END_IF
	CALLP1(SELF __MoveFilePos, 4)
	RETURN_VAL(i)
END_MEMBER_PROC

// Reads 4-byte unsigned integer from binary file.
// This function throws exception if a error appears.
MEMBER_FUNC_0(TINT, ReadUnsignedLong)
	LOCAL_VAR(TINT, i, READ_UNSIGNED_LONG(SELF __stream))
	IF(i == INVALID_INT)
		THROW(CALLF4(FormatMsg3, ErrReadFailed, SELF __name, HEXFORM(SELF __pos), T("4")))
	END_IF
	CALLP1(SELF __MoveFilePos, 4)
	RETURN_VAL(i)
END_MEMBER_PROC

// Reads 4-byte floating point number from binary file.
// This function throws exception if a error appears.
MEMBER_FUNC_0(TFLOAT, ReadFloat)
	LOCAL_VAR(TFLOAT, f, READ_FLOAT(SELF __stream))
	IF(f == INVALID_FLOAT)
		THROW(CALLF4(FormatMsg3, ErrReadFailed, SELF __name, HEXFORM(SELF __pos), T("4")))
	END_IF
	CALLP1(SELF __MoveFilePos, 4)
	RETURN_VAL(f)
END_MEMBER_PROC

// Reads a null-terminated string from binary file.
// The terminating null is read, but it is not appended to a value returned.
// This function throws exception if a error appears.
MEMBER_FUNC_0(TSTRING, ReadString)
	LOCAL_VAR(TSTRING, str, READ_STRING(SELF __stream))
	IF(str == INVALID_STRING)
		THROW(CALLF3(FormatMsg2, ErrStringTooLong, SELF __name, HEXFORM(SELF __pos)))
	END_IF
	LOCAL_VAR(TINT, sz, STRLEN(str) + 1)
	CALLP1(SELF __MoveFilePos, sz)
	RETURN_VAL(str)
END_MEMBER_PROC

// Read a line from text file.
// CR+LF are read, but they are not appended to a value returned.
// This function throws exception if a error appears.
MEMBER_FUNC_0(TSTRING, ReadLine)
	LOCAL_VAR(TSTRING, str, READ_LINE(SELF __stream))
	IF(str == INVALID_STRING)
		THROW(CALLF3(FormatMsg2, ErrLineTooLong, SELF __name, HEXFORM(SELF __pos)))
	END_IF
	ASSIGN(SELF __pos, FILE_TELL(SELF __stream))
	RETURN_VAL(str)
END_MEMBER_PROC

END_CLASS // TFile

// Global function to create object of the "TFile" class
GLOBAL_FUNC_0(TFile, NewFile)
	LOCAL_VAR(TFile, fl, NEW_VAL(TFile))
	CALLP0(fl.Init)
	RETURN_VAL(fl)
END_GLOBAL_FUNC

#endif // FILE_META
