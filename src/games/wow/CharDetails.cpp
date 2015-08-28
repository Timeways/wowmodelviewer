/*
 * CharDetails.cpp
 *
 *  Created on: 26 oct. 2013
 *
 */

#include "CharDetails.h"

#include <iostream>
#include "CharDetailsEvent.h"
#include "GameDatabase.h"
#include "TabardDetails.h"
#include "WoWModel.h"
#include "logger/Logger.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>

CharDetails::CharDetails() :
eyeGlowType(EGT_NONE), showUnderwear(true), showEars(true), showHair(true),
showFacialHair(true), showFeet(true), isNPC(true), m_model(0), race(0), gender(0),
m_skinColor(0), m_skinColorMax(0), m_faceType(0), m_faceTypeMax(0), m_hairColor(0),
m_hairColorMax(0), m_hairStyle(0), m_hairStyleMax(0), m_facialHair(0), m_facialHairMax(0)
{

}

void CharDetails::save(QXmlStreamWriter & stream)
{
  stream.writeStartElement("CharDetails");

  stream.writeStartElement("skinColor");
  stream.writeAttribute("value", QString::number(m_skinColor));
  stream.writeEndElement();

  stream.writeStartElement("faceType");
  stream.writeAttribute("value", QString::number(m_faceType));
  stream.writeEndElement();

  stream.writeStartElement("hairColor");
  stream.writeAttribute("value", QString::number(m_hairColor));
  stream.writeEndElement();

  stream.writeStartElement("hairStyle");
  stream.writeAttribute("value", QString::number(m_hairStyle));
  stream.writeEndElement();

  stream.writeStartElement("facialHair");
  stream.writeAttribute("value", QString::number(m_facialHair));
  stream.writeEndElement();

  stream.writeStartElement("eyeGlowType");
  stream.writeAttribute("value", QString::number((int)eyeGlowType));
  stream.writeEndElement();

  stream.writeStartElement("showUnderwear");
  stream.writeAttribute("value", QString::number(showUnderwear));
  stream.writeEndElement();

  stream.writeStartElement("showEars");
  stream.writeAttribute("value", QString::number(showEars));
  stream.writeEndElement();

  stream.writeStartElement("showHair");
  stream.writeAttribute("value", QString::number(showHair));
  stream.writeEndElement();

  stream.writeStartElement("showFacialHair");
  stream.writeAttribute("value", QString::number(showFacialHair));
  stream.writeEndElement();

  stream.writeStartElement("showFeet");
  stream.writeAttribute("value", QString::number(showFeet));
  stream.writeEndElement();

  stream.writeEndElement(); // CharDetails
}

void CharDetails::load(QXmlStreamReader & reader)
{
  int nbValuesRead = 0;
  while (!reader.atEnd() && nbValuesRead != 11)
  {
    if (reader.isStartElement())
    {
      if(reader.name() == "skinColor")
      {
        unsigned int skinColor = reader.attributes().value("value").toString().toUInt();
        setSkinColor(skinColor);
        nbValuesRead++;
      }

      if(reader.name() == "faceType")
      {
        unsigned int faceType = reader.attributes().value("value").toString().toUInt();
        setFaceType(faceType);
        nbValuesRead++;
      }

      if(reader.name() == "hairColor")
      {
        unsigned int hairColor = reader.attributes().value("value").toString().toUInt();
        setHairColor(hairColor);
        nbValuesRead++;
      }

      if(reader.name() == "hairStyle")
      {
        unsigned int hairStyle = reader.attributes().value("value").toString().toUInt();
        setHairStyle(hairStyle);
        nbValuesRead++;
      }

      if(reader.name() == "facialHair")
      {
        unsigned int facialHair = reader.attributes().value("value").toString().toUInt();
        setFacialHair(facialHair);
        nbValuesRead++;
      }

      if(reader.name() == "eyeGlowType")
      {
        eyeGlowType = (EyeGlowTypes)reader.attributes().value("value").toString().toUInt();
        nbValuesRead++;
      }

      if(reader.name() == "showUnderwear")
      {
        showUnderwear = reader.attributes().value("value").toString().toUInt();
        nbValuesRead++;
      }

      if(reader.name() == "showEars")
      {
        showEars = reader.attributes().value("value").toString().toUInt();
        nbValuesRead++;
      }

      if(reader.name() == "showHair")
      {
        showHair = reader.attributes().value("value").toString().toUInt();
        nbValuesRead++;
      }

      if(reader.name() == "showFacialHair")
      {
        showFacialHair = reader.attributes().value("value").toString().toUInt();
        nbValuesRead++;
      }

      if(reader.name() == "showFeet")
      {
        showFeet = reader.attributes().value("value").toString().toUInt();
        nbValuesRead++;
      }
    }
    reader.readNext();
  }
}

void CharDetails::reset(WoWModel * model)
{
  m_model = model;

  m_skinColor = 0;
  m_faceType = 0;
  m_hairColor = 0;
  m_hairStyle = 0;
  m_facialHair = 0;

  showUnderwear = true;
  showHair = true;
  showFacialHair = true;
  showEars = true;
  showFeet = false;

  isNPC = false;

  updateMaxValues();
}

void CharDetails::setSkinColor(size_t val)
{
  if(val != m_skinColor)
  {
    m_skinColor = val;
    updateMaxValues();
    CharDetailsEvent event(this, CharDetailsEvent::SKINCOLOR_CHANGED);
    notify(event);
  }
}

void CharDetails::setFaceType(size_t val)
{
  if(val != m_faceType)
  {
    m_faceType = val;
    updateMaxValues();
    CharDetailsEvent event(this, CharDetailsEvent::FACETYPE_CHANGED);
    notify(event);
  }
}

void CharDetails::setHairColor(size_t val)
{
  if(val != m_hairColor)
  {
    m_hairColor = val;
    updateMaxValues();
    CharDetailsEvent event(this, CharDetailsEvent::HAIRCOLOR_CHANGED);
    notify(event);
  }
}

void CharDetails::setHairStyle(size_t val)
{
  if(val != m_hairStyle)
  {
    m_hairStyle = val;
    updateMaxValues();
    CharDetailsEvent event(this, CharDetailsEvent::HAIRSTYLE_CHANGED);
    notify(event);
  }
}

void CharDetails::setFacialHair(size_t val)
{
  if(val != m_facialHair)
  {
    m_facialHair = val;
    updateMaxValues();
    CharDetailsEvent event(this, CharDetailsEvent::FACIALHAIR_CHANGED);
    notify(event);
  }
}

void CharDetails::updateMaxValues()
{
  if(!m_model)
    return;

  m_faceTypeMax = getNbValuesForSection(FaceType);
  m_skinColorMax = getNbValuesForSection(SkinType);
  m_hairColorMax = getNbValuesForSection(HairType);

  RaceInfos infos;
  RaceInfos::getCurrent(m_model->name().toStdString(), infos);

  QString query = QString("SELECT MAX(VariationIndex) FROM CharSections WHERE RaceID=%1 AND SexID=%2 AND SectionType=%3")
                        .arg(race)
                        .arg(gender)
                        .arg(infos.isHD?8:3);

  sqlResult hairStyles = GAMEDATABASE.sqlQuery(query);

  if(hairStyles.valid && !hairStyles.values.empty())
  {
    m_hairStyleMax = hairStyles.values[0][0].toInt();
  }
  else
  {
    LOG_ERROR << "Unable to collect number of hair styles for model" << m_model->name();
    m_hairStyleMax = 0;
  }


  query = QString("SELECT MAX(VariationID) FROM CharacterFacialHairStyles WHERE RaceID=%1 AND SexID=%2")
                            .arg(race)
                            .arg(gender);

  sqlResult facialHairStyles = GAMEDATABASE.sqlQuery(query);
  if(facialHairStyles.valid && !facialHairStyles.values.empty())
  {
    m_facialHairMax = facialHairStyles.values[0][0].toInt();
  }
  else
  {
    LOG_ERROR << "Unable to collect number of facial hair styles for model" << m_model->name();
    m_facialHairMax = 0;
  }

  if (m_faceTypeMax == 0) m_faceTypeMax = 1;
  if (m_skinColorMax == 0) m_skinColorMax = 1;
  if (m_hairColorMax == 0) m_hairColorMax = 1;
  if (m_hairStyleMax == 0) m_hairStyleMax = 1;
  if (m_facialHairMax == 0) m_facialHairMax = 1;
}

std::vector<std::string> CharDetails::getTextureNameForSection(SectionType section)
{
  std::vector<std::string> result;

  RaceInfos infos;
  if(!RaceInfos::getCurrent(m_model->name().toStdString(), infos))
    return result;

/*
  std::cout << __FUNCTION__ << std::endl;
  std::cout << "----------------------------------------------" << std::endl;
  std::cout << "infos.raceid = " << infos.raceid << std::endl;
  std::cout << "infos.sexid = " << infos.sexid << std::endl;
  std::cout << "infos.textureLayoutID = " << infos.textureLayoutID << std::endl;
  std::cout << "infos.isHD = " << infos.isHD << std::endl;
  std::cout << "cd.skinColor() = " << skinColor() << std::endl;
  std::cout << "section = " << section << std::endl;

  std::cout << "----------------------------------------------" << std::endl;
*/

  size_t type = section;

  if(infos.isHD) // HD layout
    type+=5;

  QString query;
  switch(section)
  {
    case SkinType:
    case UnderwearType:
      query = QString("SELECT TextureName1, TextureName2, TextureName3 FROM CharSections WHERE \
              (RaceID=%1 AND SexID=%2 AND ColorIndex=%3 AND SectionType=%4)")
              .arg(infos.raceid)
              .arg(infos.sexid)
              .arg(skinColor())
              .arg(type);
      break;
    case FaceType:
      query = QString("SELECT TextureName1, TextureName2, TextureName3 FROM CharSections WHERE \
              (RaceID=%1 AND SexID=%2 AND ColorIndex=%3 AND VariationIndex=%4 AND SectionType=%5)")
              .arg(infos.raceid)
              .arg(infos.sexid)
              .arg(skinColor())
              .arg(faceType())
              .arg(type);
      break;
    case HairType:
        query = QString("SELECT TextureName1, TextureName2, TextureName3 FROM CharSections \
              WHERE (RaceID=%1 AND SexID=%2 AND VariationIndex=%3 AND ColorIndex=%4 AND SectionType=%5)")
              .arg(infos.raceid)
              .arg(infos.sexid)
              .arg(hairStyle()?hairStyle():1)
              .arg(hairColor())
              .arg(type);
      break;
    case FacialHairType:
      query = QString("SELECT TextureName1, TextureName2, TextureName3 FROM CharSections WHERE \
                  (RaceID=%1 AND SexID=%2 AND VariationIndex=%3 AND ColorIndex=%4 AND SectionType=%5)")
                  .arg(infos.raceid)
                  .arg(infos.sexid)
                  .arg(facialHair())
                  .arg(hairColor())
                  .arg(type);
      break;
    default:
      query = "";
  }

  if(query != "")
  {
    sqlResult vals = GAMEDATABASE.sqlQuery(query);
    if(vals.valid && !vals.values.empty())
    {
      for(size_t i = 0; i < vals.values[0].size() ; i++)
        if(!vals.values[0][i].isEmpty())
          result.push_back(vals.values[0][i].toStdString());
    }
    else
    {
      LOG_ERROR << "Unable to collect infos for model";
      LOG_ERROR << query << vals.valid << vals.values.size();
    }
  }

  return result;
}

int CharDetails::getNbValuesForSection(SectionType section)
{
  int result = 0;

  RaceInfos infos;
  if(!RaceInfos::getCurrent(m_model->name().toStdString(), infos))
    return result;

  size_t type = section;

  if(infos.isHD)
    type+=5;

  QString query;
  switch(section)
  {
    case SkinType:
      query = QString("SELECT COUNT(*)-1 FROM CharSections WHERE RaceID=%1 AND SexID=%2 AND SectionType=%3")
              .arg(infos.raceid)
              .arg(infos.sexid)
              .arg(type);
      break;
    case FaceType:
      query = QString("SELECT COUNT(*)-1 FROM CharSections WHERE RaceID=%1 AND SexID=%2 AND ColorIndex=%3 AND SectionType=%4")
              .arg(infos.raceid)
              .arg(infos.sexid)
              .arg(skinColor())
              .arg(type);
      break;
    case HairType:
      query = QString("SELECT COUNT(*)-1 FROM CharSections WHERE RaceID=%1 AND SexID=%2 AND VariationIndex=%3 AND SectionType=%4")
              .arg(infos.raceid)
              .arg(infos.sexid)
              .arg(hairStyle())
              .arg(type);
      break;
    default:
      query = "";
  }

  sqlResult vals = GAMEDATABASE.sqlQuery(query);

  if(vals.valid && !vals.values.empty())
  {
    result = vals.values[0][0].toInt();

  }
  else
  {
    LOG_ERROR << "Unable to collect number of customization for model" << m_model->name();
  }

  return result;
}