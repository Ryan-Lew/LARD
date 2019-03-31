#include <cmath>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <QTextCodec>
#include "Utility.h"




void OrthogonalToPolar(double x,double y,double* rho,double* theta)
{
	*rho = sqrt(x*x + y*y);
	if ( (*rho)>0.0 )
	{
		*theta = ( y > 0.0) ? acos( x / *rho ) : ( MY_2PI - acos( x / *rho ) );
	}
	else
	{
		*theta = 0;
	}
	*theta = ( *theta ) * 360.0 / MY_2PI;
}

void PolarToOrthogonal(double rho,double theta,double* x,double* y)
{
	theta = theta / 360.0 * MY_2PI;
	*x = rho * cos(theta);
	*y = rho * sin(theta);
}



QString Chinese(const std::string& str)
{
	return QTextCodec::codecForLocale()->toUnicode(str.c_str());
}

/// Memory order HIGH-LOW 
UINT16 TwoBytesToUINT16(const BYTE* two_bytes)
{
	return ( ((UINT16)(*(two_bytes))) << 8 ) | ((UINT16)(*(two_bytes + 1)));

}

/// Memory order HIGH-LOW 
void UINT16ToTwoBytes(UINT16 word,BYTE* two_bytes)
{
	*(two_bytes)     = *((BYTE*)(&word) + 1);
	*(two_bytes + 1) = *((BYTE*)(&word));
}

/// Memory order HIGH-LOW 
UINT32 FourBytesToUINT32(const BYTE* four_bytes)
{
	return ( ( (UINT32)(*four_bytes) ) << 24 ) | ( ( (UINT32)(*(four_bytes + 1)) ) << 16 ) | ( ( (UINT32)(*(four_bytes + 2) ) ) << 8 ) | ( (UINT32)(*(four_bytes + 3)) );

}


/// Memory order HIGH-LOW 
void UINT32ToFourBytes(UINT32 dword,BYTE* four_bytes)
{
	*(four_bytes)     = *( (BYTE*)(&dword) + 3 );
	*(four_bytes + 1) = *( (BYTE*)(&dword) + 2 );
	*(four_bytes + 2) = *( (BYTE*)(&dword) + 1 );
	*(four_bytes + 3) = *( (BYTE*)(&dword));
}

BYTE GetBitValue(BYTE data,BYTE pos)
{
	return (data >> pos) &  0x01;	
}

void SetBitValue(BYTE* data,BYTE pos)
{
	*data = (*data) | ( 0x01 << pos );
}

void ClearBitValue(BYTE* data, byte pos)
{
	*data = (*data) & (~(0x01 << pos));
}


std::vector<std::string> LoadWorkFrequency()
{
	std::ifstream ifs;
	ifs.open( (DATA_PATH + "Work_Frequency.txt").c_str() );
	std::map<float,std::string> str_list;
	std::string in_str;
	while (std::getline(ifs,in_str))
	{
		bool    str_ok = false;
		float   fre = QString(in_str.c_str()).toFloat(&str_ok);
		if (str_ok)
		{
			str_list.insert(std::make_pair(fre,in_str));
		}
	}
	ifs.close();
	std::vector<std::string> str_list_return;
	for(std::map<float,std::string>::const_iterator pos = str_list.begin(); pos != str_list.end(); ++pos)
	{
		str_list_return.push_back(pos->second);
	}
	return str_list_return;
}

