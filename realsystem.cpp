#include "realsystem.hpp"


#include <fstream>
#include <iostream>
#include <chrono>
#include <jsoncpp/json/reader.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/StreamCopier.h>
#include <Poco/InflatingStream.h>
#include <QUrl>
#include <QDesktopServices>
#include "escapedtags.hpp"


using std::ifstream;
using std::istream;
using std::cerr;
using std::string;
namespace chrono = std::chrono;
namespace Net = Poco::Net;
using Net::HTTPResponse;


static const char *old_questions_path = "old_questions.json";
static const char *new_questions_path = "new_questions.json";


static void playSound(const std::string &path)
{
  system(("aplay "+path).c_str());
}


static Questions getQuestionsFrom(const Json::Value &root_value)
{
  Questions result;

  using Json::ValueType;
  ValueType root_type = root_value.type();

  if (root_type!=ValueType::objectValue) {
    cerr << "Root type is not an object\n";
    return {};
  }

  using Json::Value;

  const Value& items_value = root_value["items"];

  for (const auto& item_value : items_value) {
    if (item_value["closed_date"].asString()=="") {
      Question question;
      question.title         = item_value["title"].asString();
      question.link          = item_value["link"].asString();
      question.creation_date = item_value["creation_date"].asInt64();
      question.id            = item_value["question_id"].asInt();

      result.push_back(question);
    }
  }

  return result;
}


static Questions readQuestionsFrom(const char *path)
{
  ifstream stream(path);
  if (!stream) return {};
  Json::Reader reader;
  Json::Value root_value;
  reader.parse(stream,root_value);
  Questions questions = getQuestionsFrom(root_value);
  return questions;
}


static int getQuestions(const char *path,const string &escaped_tags)
{
  string path_and_query =
    "/2.2/search"
    "?order=desc"
    "&sort=creation"
    "&tagged="+escaped_tags+
    "&filter=default"
    "&site=stackoverflow"
    "&run=true";
  Poco::URI uri("http://api.stackexchange.com");
  Net::HTTPClientSession session(uri.getHost(),uri.getPort());
  Net::HTTPRequest request(Net::HTTPRequest::HTTP_GET,path_and_query);
  HTTPResponse response;
  session.sendRequest(request);
  istream& response_stream = session.receiveResponse(response);
  HTTPResponse::HTTPStatus status = response.getStatus();

  auto STREAM_GZIP = Poco::InflatingStreamBuf::STREAM_GZIP;
  Poco::InflatingInputStream
    inflated_response_stream(response_stream,STREAM_GZIP);

  if (status!=HTTPResponse::HTTP_OK) {
    cerr << "status=" << status << "\n";
    return EXIT_FAILURE;
  }

  std::ofstream stream(path);
  Poco::StreamCopier::copyStream(inflated_response_stream,stream);
  cerr << "Saved to " << path << "\n";

  return EXIT_SUCCESS;
}


Questions RealSystem::readStoredOldQuestions()
{
  return readQuestionsFrom(old_questions_path);
}


Questions RealSystem::readStoredNewQuestions()
{
  return readQuestionsFrom(new_questions_path);
}


void RealSystem::updateStoredQuestions(const string &tags)
{
  rename(new_questions_path,old_questions_path);
  string escaped_tags = escapedTags(tags);
  getQuestions(new_questions_path,escaped_tags);
}


void RealSystem::playNewQuestionsSound()
{
  playSound("/usr/share/scratch/Media/Sounds/Effects/Pop.wav");
}


void RealSystem::openLink(const string &link)
{
  QUrl url(link.c_str());
  QDesktopServices::openUrl(url);
}


double RealSystem::currentTime()
{
  auto now = chrono::system_clock::now();
  chrono::duration<double> time_since_epoch_in_seconds_as_double =
    chrono::duration_cast<chrono::seconds>(now.time_since_epoch());
  return time_since_epoch_in_seconds_as_double.count();
}
