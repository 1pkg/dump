#include "Writer.hpp"
#include "ColorDeck.hpp"
#include "StrAlgh.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <tinyxml.h>

Writer::Writer(const std::string &fileName, const ColorDeck &link)
    : _fileName(fileName), _link(link), _fileExt(getFileExt(fileName)) {
  if (!rightName(fileName, ".xml|.png|.jpeg|.jpg|.bmp|.tiff"))
    throw std::exception();
}

void Writer::write() const {
  if (_fileExt == "xml")
    _writeXML();
  else
    _writeIMAGE();
}

void Writer::_writeIMAGE() const {

  cv::Mat img(_link.getWidth(), _link.getLen(), CV_8UC3);

  cv::Vec3b colors;
  Color color;
  bool fail = false;

  for (int i = 0; i < _link.getWidth(); i++) {
    for (int j = 0; j < _link.getLen(); j++) {
      color = _link.getItem(Coordinate(i, j), fail);

      if (fail) {
        colors[0] = 255;
        colors[1] = 255;
        colors[2] = 255;
      } else {
        colors[0] = color.getRedPart();
        colors[1] = color.getGreenPart();
        colors[2] = color.getBluePart();
      }

      img.at<cv::Vec3b>(cv::Point(j, i)) = colors;

      fail = false;
      colors[0] = 0;
      colors[1] = 0;
      colors[2] = 0;
    }
  }

  cv::imwrite(_fileName, img);
}

void Writer::_writeXML() const {
  TiXmlDocument doc;
  TiXmlElement *element;
  TiXmlText *text;

  TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "", "");
  doc.LinkEndChild(decl);
  TiXmlElement *colorDeck = new TiXmlElement("colorDeck");
  doc.LinkEndChild(colorDeck);

  TiXmlElement *lenght = new TiXmlElement("lenght");
  auto len = _link.getLen();
  text = new TiXmlText(std::to_string(len).data());
  lenght->LinkEndChild(text);
  colorDeck->LinkEndChild(lenght);

  TiXmlElement *width = new TiXmlElement("width");
  auto widtH = _link.getWidth();
  text = new TiXmlText(std::to_string(widtH).data());
  width->LinkEndChild(text);
  colorDeck->LinkEndChild(width);

  auto stream = _link.serialize();
  std::string str;
  while (stream >> str) {

    element = new TiXmlElement("color");
    text = new TiXmlText(str.data());
    element->LinkEndChild(text);
    colorDeck->LinkEndChild(element);
    str.clear();
  }

  doc.SaveFile(_fileName.data());
}
