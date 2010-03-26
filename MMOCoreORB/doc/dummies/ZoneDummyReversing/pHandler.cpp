#include "pHandler.h"

unsigned int GenerateCrc(char* pData,unsigned short nLength,unsigned int nCrcSeed)
{
    unsigned int nCrc = g_nCrcTable[(~nCrcSeed) & 0xFF];
    nCrc ^= 0x00FFFFFF;
    unsigned int nIndex = (nCrcSeed >> 8) ^ nCrc;
    nCrc = (nCrc >> 8) & 0x00FFFFFF;
    nCrc ^= g_nCrcTable[nIndex & 0xFF];
    nIndex = (nCrcSeed >> 16) ^ nCrc;
    nCrc = (nCrc >> 8) & 0x00FFFFFF;
    nCrc ^= g_nCrcTable[nIndex & 0xFF];
    nIndex = (nCrcSeed >> 24) ^ nCrc;
    nCrc = (nCrc >> 8) &0x00FFFFFF;
    nCrc ^= g_nCrcTable[nIndex & 0xFF];

    for( short i = 0; i < nLength; i++ )
    {
        nIndex = (pData[i]) ^ nCrc;
        nCrc = (nCrc >> 8) & 0x00FFFFFF;
        nCrc ^= g_nCrcTable[nIndex & 0xFF];
    }
    return ~nCrc;
}


bool CrcTest(char *pData, unsigned short nLength,unsigned int nCrcSeed, short nCrcLength)
{
    bool crctest = true;
    if(nCrcLength > 0)
    {
        unsigned int p_crc = GenerateCrc(pData,(nLength-nCrcLength),nCrcSeed);
        unsigned int  crc = 0;
        unsigned int mask = 0;
        unsigned int pullbyte = 0;
        pData = pData + (nLength-nCrcLength);
        for( short i = 0; i < nCrcLength; i++ )
        {
            pullbyte = (unsigned char)pData[i];
            crc |=(pullbyte << (((nCrcLength - 1) - i) * 8));
            mask <<= 8;
            mask |= 0xFF;
        }
        p_crc &= mask;
        if(p_crc != crc)
            crctest = false;
    }
    return crctest;
}

void AppendCRC(char *pData, unsigned short nLength, unsigned int nCrcSeed, short nCrcLength)
{
    if (nCrcLength > 0)
    {
        unsigned int crc = GenerateCrc(pData,(nLength-nCrcLength),nCrcSeed);
        pData += (nLength-nCrcLength);
        for( short i = 0; i < nCrcLength; i++ )
        {
            pData[(nCrcLength - 1) - i] = (char)((crc >> (8 * i)) & 0xFF);
        }
    }

}


void Decrypt(char *pData,unsigned short nLength,unsigned int nCrcSeed)
{
    unsigned int *Data;
    if(pData[0] == 0x00)
    {
     nLength-=4;
     Data = (unsigned int*)(pData+2);
    }
    else
    {
     nLength-=3;
     Data = (unsigned int*)(pData+1);
    }
    short block_count = (nLength / 4);
    short byte_count = (nLength % 4);
    unsigned int itemp;
    for(short count = 0;count<block_count;count++)
    {
        itemp = *Data;
        *Data ^= nCrcSeed;
        nCrcSeed = itemp;
        Data++;
    }
    pData = (char*)Data;
    for(short count = 0;count<byte_count;count++)
    {
        *pData ^= nCrcSeed;
        pData++;
    }
}

void Encrypt(char *pData, unsigned short nLength,unsigned int nCrcSeed)
{
    unsigned int *Data;
    if(pData[0] == 0x00)
    {
     nLength-=4;
     Data = (unsigned int*)(pData+2);
    }
    else
    {
     nLength-=3;
     Data = (unsigned int*)(pData+1);
    }
    short block_count = (nLength / 4);
    short byte_count = (nLength % 4);
    unsigned int itemp;
    for(short count = 0;count<block_count;count++)
    {
        *Data ^= nCrcSeed;
        nCrcSeed = *Data;
        Data++;
    }
    pData = (char*)Data;
    for(short count = 0;count<byte_count;count++)
    {
        *pData ^= (char)nCrcSeed;
        pData++;
    }
}

char *Decompress(char *pData, unsigned short &nLength)
{
    
    unsigned short offset;
    if(pData[0] == 0x00)
     offset = 2;
    else
     offset = 1;
    z_stream packet;
    char output[CompBuf];
    unsigned short newLength=0;
    packet.zalloc = Z_NULL;
    packet.zfree = Z_NULL;
    packet.opaque = Z_NULL;
    packet.avail_in = 0;
    packet.next_in = Z_NULL;
    inflateInit(&packet);
    packet.next_in = (Bytef*)(pData+offset);
    packet.avail_in = (nLength - offset -3);
    packet.next_out = (Bytef*)output;
    packet.avail_out = CompBuf;
    inflate(&packet,Z_FINISH);
    newLength = packet.total_out;
    inflateEnd(&packet);
    char *Decomp_pData  = new char [newLength + offset + 3];
    char *begDecomp_pData = Decomp_pData;
    *Decomp_pData = pData[0];
    Decomp_pData++;
    if(offset == 2)
	{
	 *Decomp_pData = pData[1];
     Decomp_pData++;
	}
    for(short x=0;x<newLength;x++)
    {
        *Decomp_pData = output[x];
        Decomp_pData++;
    }
	*Decomp_pData = 0x01;
    Decomp_pData++;
	pData += (nLength-2);
    *(unsigned short*)Decomp_pData = *(unsigned short*)pData;
    Decomp_pData = begDecomp_pData;
    nLength = newLength + offset + 3;
    return Decomp_pData;

}

char *Compress(char *pData, unsigned short &nLength)
{
 unsigned short offset;
 if(pData[0] == 0x00)
   offset = 2;
 else
   offset = 1;
 z_stream packet;
 char *output = new char[nLength+20];
 packet.zalloc = Z_NULL;
 packet.zfree = Z_NULL;
 packet.opaque = Z_NULL;
 packet.avail_in = 0;
 packet.next_in = Z_NULL;
 deflateInit(&packet,Z_DEFAULT_COMPRESSION);
 packet.next_in = (Bytef* )(pData+offset);
 packet.avail_in = nLength - offset - 3;
 packet.next_out = (Bytef* )output;
 packet.avail_out = nLength + 20;
 deflate(&packet,Z_FINISH);
 unsigned short newLength = packet.total_out;
 deflateEnd(&packet);
 char *comp_pData  = new char [newLength+ offset + 3];
 char *begcomp_pData;
 begcomp_pData = comp_pData;
 *comp_pData = pData[0];
 comp_pData++;
 if(offset == 2)
 {
   *comp_pData = pData[1];
   comp_pData++;
 }
 for(short x=0;x<newLength;x++)
 {
  *comp_pData = output[x];
  comp_pData++;
  }
 *comp_pData = 0x01;
 comp_pData++;
 pData += (nLength-2);
 *(unsigned short*)comp_pData = *(unsigned short*)pData;
 comp_pData = begcomp_pData;
 nLength = newLength + offset + 3;
 return comp_pData;
}


