#include "openlink.hpp"

#include <QUrl>
#include <QDesktopServices>


void openLink(const std::string &link)
{
  QUrl url(link.c_str());
  QDesktopServices::openUrl(url);
}
