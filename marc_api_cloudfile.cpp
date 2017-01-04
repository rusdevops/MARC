#include "marc_api_cloudfile.h"

CloudFile::CloudFile()
{

}

CloudFile::Type CloudFile::getType() const
{
    return type;
}

void CloudFile::setType(const Type &value)
{
    type = value;
}

std::string CloudFile::getKind() const
{
    return kind;
}

void CloudFile::setKind(const std::string &value)
{
    kind = value;
}

std::string CloudFile::getHome() const
{
    return home;
}

void CloudFile::setHome(const std::string &value)
{
    home = value;
}

std::string CloudFile::getName() const
{
    return name;
}

void CloudFile::setName(const std::string &value)
{
    name = value;
}

std::string CloudFile::getHash() const
{
    return hash;
}

void CloudFile::setHash(const std::string &value)
{
    hash = value;
}

uint64_t CloudFile::getMtime() const
{
    return mtime;
}

void CloudFile::setMtime(const uint64_t &value)
{
    mtime = value;
}

uint64_t CloudFile::getSize() const
{
    return size;
}

void CloudFile::setSize(const uint64_t &value)
{
    size = value;
}

std::string CloudFile::getVirusScan() const
{
    return virusScan;
}

void CloudFile::setVirusScan(const std::string &value)
{
    virusScan = value;
}