#include "data.hpp"

#include <fstream>
#include <iostream>
#include <jsoncpp/json/reader.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/StreamCopier.h>
#include <Poco/InflatingStream.h>
#include <QDesktopServices>


using std::ifstream;
using std::istream;
using std::cerr;
namespace Net = Poco::Net;
using Net::HTTPResponse;


static const char *old_questions_path = "old_questions.json";
static const char *new_questions_path = "new_questions.json";


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
    Question question;
    question.title         = item_value["title"].asString();
    question.link          = item_value["link"].asString();
    question.creation_date = item_value["creation_date"].asInt64();
    question.id            = item_value["question_id"].asInt();

    result.push_back(question);
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


static int getQuestions(const char *path)
{
  std::string path_and_query =
    "/2.2/questions"
    "?order=desc"
    "&sort=creation"
    "&tagged=c%2B%2B"
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


Data::Data()
{
  readExisting();
}


void Data::readExisting()
{
  old_questions = readQuestionsFrom(old_questions_path);
  new_questions = readQuestionsFrom(new_questions_path);
}


void Data::update()
{
  rename(new_questions_path,old_questions_path);
  getQuestions(new_questions_path);
  old_questions = new_questions;
  new_questions = readQuestionsFrom(new_questions_path);
}
