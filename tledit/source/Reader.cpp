#include "Reader.hpp"
#include "ColorDeck.hpp"
#include "StrAlgh.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <tinyxml.h>

Reader::Reader(const std::string &fileName, ColorDeck &link)
    : _fileName(fileName), _link(link), _fileExt(getFileExt(fileName)) {

  if (!rightName(fileName, ".xml|.png|.jpeg|.jpg|.bmp|.tiff"))
    throw std::exception();
}

void Reader::read() {
  if (_fileExt == "xml")
    _readXML();
  else
    _readIMAGE();
}

void Reader::_readIMAGE() {

  cv::Mat img;

  img = cv::imread(_fileName);

  cv::Vec3b colors;
  Color color;

  _link = ColorDeck(img.size().width, img.size().height);

  for (int i = 0; i < img.size().height; i++) {
    for (int j = 0; j < img.size().width; j++) {
      colors = img.at<cv::Vec3b>(cv::Point(j, i));

      color.setRedPart(colors[0]);
      color.setGreenPart(colors[1]);
      color.setBluePart(colors[2]);

      _link.setItem(Coordinate(i, j), color);
    }
  }
}

void Reader::_readXML() {

  TiXmlDocument doc(_fileName.data());

  if (!doc.LoadFile())
    throw std::exception();

  std::stringstream stream;

  TiXmlElement *sizeEl =
      doc.FirstChildElement("colorDeck")->FirstChildElement("lenght");
  auto len = atoi(sizeEl->GetText());
  sizeEl = doc.FirstChildElement("colorDeck")->FirstChildElement("width");
  auto width = atoi(sizeEl->GetText());

  TiXmlElement *element =
      doc.FirstChildElement("colorDeck")->FirstChildElement("color");
  for (element; element; element = element->NextSiblingElement()) {

    stream << element->GetText();
    stream << '\n';
  }

  _link = ColorDeck::unserialize(stream, len, width);
}