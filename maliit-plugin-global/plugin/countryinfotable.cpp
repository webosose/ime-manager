// Copyright (c) 2013-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#include "countryinfotable.h"

#include <QHash>
#include <QLocale>

typedef QHash<QString, CountryInfoElement> CountryHash;

QScopedPointer<CountryInfoTable> CountryInfoTable::s_instance;      // used for singleton
static CountryHash s_countryHash;
static QHash<QString, QLocale::Country> s_hash3166;

CountryInfoTable *CountryInfoTable::getInstance()
{
    if (s_instance.isNull())
        s_instance.reset(new CountryInfoTable());
    return s_instance.data();
}

CountryInfoTable::CountryInfoTable()
{
    init();
}

CountryInfoTable::~CountryInfoTable()
{
}

void CountryInfoTable::releaseInstance()
{
    if (!s_instance.isNull())
        s_instance.reset();
}

QString CountryInfoTable::getCountryCode(QString country)
{
    CountryHash::const_iterator it = s_countryHash.find(country);
    if (it != s_countryHash.end())
        return it.value().countryCode;
    else
        return "";
}

QStringList CountryInfoTable::getUrlSuggestions(QString country)
{
    CountryHash::const_iterator it = s_countryHash.find(country);
    if (it != s_countryHash.end())
        return it.value().urlSuggestions.split(" ");
    else {
        QStringList list;
        list << ".com" << ".org" << "/";
        return list;
    }
}

QStringList CountryInfoTable::getEmailSuggestions(QString country)
{
    CountryHash::const_iterator it = s_countryHash.find(country);
    if (it != s_countryHash.end())
        return it.value().emailSuggestions.split(" ");
    else {
        QStringList list;
        list << ".com" << ".org" << "/";
        return list;
    }
}

QString CountryInfoTable::conv3166ToCountryString(QString iso3166Code)
{
    QHash<QString, QLocale::Country>::const_iterator it = s_hash3166.find(iso3166Code.toUpper());
    if (it != s_hash3166.end())
        return QLocale::countryToString(it.value());
    else
        return "";
}

int CountryInfoTable::conv3166ToCountryLocale(QString iso3166Code)
{
    QHash<QString, QLocale::Country>::const_iterator it = s_hash3166.find(iso3166Code.toUpper());
    if (it != s_hash3166.end())
        return it.value();
    else
        return QLocale::AnyCountry;
}

void CountryInfoTable::init()
{
    // initialize table
    s_countryHash.reserve(300);

    s_countryHash.insert(QLocale::countryToString(QLocale::Afghanistan),
                         CountryInfoElement(QString("af"),  QString("http:// https:// www. .com .com.af /"),  QString(".com .com.af /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Albania),
                         CountryInfoElement(QString("al"),  QString("http:// https:// www. .com .com.al /"),  QString(".com .com.al /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Algeria),
                         CountryInfoElement(QString("dz"),  QString("http:// https:// www. .com .dz /"),      QString(".com .dz /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::AmericanSamoa),
                         CountryInfoElement(QString("as"),  QString("http:// https:// www. .com .as /"),      QString(".com .as /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Andorra),
                         CountryInfoElement(QString("ad"),  QString("http:// https:// www. .com .ad /"),      QString(".com .ad /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Angola),
                         CountryInfoElement(QString("ao"),  QString("http:// https:// www. .com .co.ao /"),   QString(".com .co.ao /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Anguilla),
                         CountryInfoElement(QString("ai"),  QString("http:// https:// www. .com .com.ai /"),  QString(".com .com.ai /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Antarctica),
                         CountryInfoElement(QString("aq"),  QString("http:// https:// www. .com .aq /"),      QString(".com .aq /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::AntiguaAndBarbuda),
                         CountryInfoElement(QString("ag"),  QString("http:// https:// www. .com .com.ag /"),  QString(".com .com.ag /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Argentina),
                         CountryInfoElement(QString("ar"),  QString("http:// https:// www. .com .com.ar /"),  QString(".com .com.ar /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Armenia),
                         CountryInfoElement(QString("am"),  QString("http:// https:// www. .com .am /"),      QString(".com .am /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Aruba),
                         CountryInfoElement(QString("aw"),  QString("http:// https:// www. .com .com.aw /"),  QString(".com .com.aw /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Australia),
                         CountryInfoElement(QString("au"),  QString("http:// https:// www. .com .com.au /"),  QString(".com .com.au /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Austria),
                         CountryInfoElement(QString("at"),  QString("http:// https:// www. .com .co.at /"),   QString(".com .co.at /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Azerbaijan),
                         CountryInfoElement(QString("az"),  QString("http:// https:// www. .com .com.az /"),  QString(".com .com.az /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Bahamas),
                         CountryInfoElement(QString("bs"),  QString("http:// https:// www. .com .bs /"),      QString(".com .bs /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Bahrain),
                         CountryInfoElement(QString("bh"),  QString("http:// https:// www. .com .com.bh /"),  QString(".com .com.bh /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Bangladesh),
                         CountryInfoElement(QString("bd"),  QString("http:// https:// www. .com .bd /"),      QString(".com .bc /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Barbados),
                         CountryInfoElement(QString("bb"),  QString("http:// https:// www. .com .bb /"),      QString(".com .bb /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Belarus),
                         CountryInfoElement(QString("by"),  QString("http:// https:// www. .com .by /"),      QString(".com .by /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Belgium),
                         CountryInfoElement(QString("be"),  QString("http:// https:// www. .com .be /"),      QString(".com .be /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Belize),
                         CountryInfoElement(QString("bz"),  QString("http:// https:// www. .com .bz /"),      QString(".com .bz /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Benin),
                         CountryInfoElement(QString("bj"),  QString("http:// https:// www. .com .bj /"),      QString(".com .bj /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Bermuda),
                         CountryInfoElement(QString("bm"),  QString("http:// https:// www. .com .bm /"),      QString(".com .bm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Bhutan),
                         CountryInfoElement(QString("bt"),  QString("http:// https:// www. .com .bt /"),      QString(".com .bt /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Bolivia),
                         CountryInfoElement(QString("bo"),  QString("http:// https:// www. .com .bo /"),      QString(".com .bo /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::BosniaAndHerzegowina),
                         CountryInfoElement(QString("ba"),  QString("http:// https:// www. .com .ba /"),      QString(".com .ba /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Botswana),
                         CountryInfoElement(QString("bw"),  QString("http:// https:// www. .com .co.bw /"),   QString(".com .co.bw /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::BouvetIsland),
                         CountryInfoElement(QString("bv"),  QString("http:// https:// www. .com .no /"),      QString(".com .no /")));  // there are no plans for "bv". It follows the policy of "no"
    s_countryHash.insert(QLocale::countryToString(QLocale::Brazil),
                         CountryInfoElement(QString("br"),  QString("http:// https:// www. .com .br /"),      QString(".com .br /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::BritishIndianOceanTerritory),
                         CountryInfoElement(QString("io"),  QString("http:// https:// www. .com .io /"),      QString(".com .io /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Brunei),
                         CountryInfoElement(QString("bn"),  QString("http:// https:// www. .com .bn /"),      QString(".com .bn /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Bulgaria),
                         CountryInfoElement(QString("bg"),  QString("http:// https:// www. .com .bg /"),      QString(".com .bg /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::BurkinaFaso),
                         CountryInfoElement(QString("bf"),  QString("http:// https:// www. .com .bf /"),      QString(".com .bf /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Burundi),
                         CountryInfoElement(QString("bi"),  QString("http:// https:// www. .com .bi /"),      QString(".com .bi /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Cambodia),
                         CountryInfoElement(QString("kh"),  QString("http:// https:// www. .com .kh /"),      QString(".com .kh /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Cameroon),
                         CountryInfoElement(QString("cm"),  QString("http:// https:// www. .com .cm /"),      QString(".com .cm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Canada),
                         CountryInfoElement(QString("ca"),  QString("http:// https:// www. .com .ca /"),      QString(".com .ca /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::CapeVerde),
                         CountryInfoElement(QString("cv"),  QString("http:// https:// www. .com .cv /"),      QString(".com .cv /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::CaymanIslands),
                         CountryInfoElement(QString("ky"),  QString("http:// https:// www. .com .ky /"),      QString(".com .ky /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::CentralAfricanRepublic),
                         CountryInfoElement(QString("cf"),  QString("http:// https:// www. .com .cf /"),      QString(".com .cf /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Chad),
                         CountryInfoElement(QString("td"),  QString("http:// https:// www. .com .td /"),      QString(".com .td /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Chile),
                         CountryInfoElement(QString("cl"),  QString("http:// https:// www. .com .co.cl /"),   QString(".com .co.cl /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::China),
                         CountryInfoElement(QString("cn"),  QString("http:// https:// www. .com .cn /"),      QString(".com .cn /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::ChristmasIsland),
                         CountryInfoElement(QString("cx"),  QString("http:// https:// www. .com .cx /"),      QString(".com .cx /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::CocosIslands),
                         CountryInfoElement(QString("cc"),  QString("http:// https:// www. .com .cc /"),      QString(".com .cc /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Colombia),
                         CountryInfoElement(QString("co"),  QString("http:// https:// www. .com .co /"),      QString(".com .co /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Comoros),
                         CountryInfoElement(QString("km"),  QString("http:// https:// www. .com .km /"),      QString(".com .km /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::CongoKinshasa),
                         CountryInfoElement(QString("cd"),  QString("http:// https:// www. .com .cd /"),      QString(".com .cd /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::CongoBrazzaville),
                         CountryInfoElement(QString("cg"),  QString("http:// https:// www. .com .cg /"),      QString(".com .cg /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::CookIslands),
                         CountryInfoElement(QString("ck"),  QString("http:// https:// www. .com .ck /"),      QString(".com .ck /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::CostaRica),
                         CountryInfoElement(QString("cr"),  QString("http:// https:// www. .com .co.cr /"),   QString(".com .co.cr /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Croatia),
                         CountryInfoElement(QString("hr"),  QString("http:// https:// www. .com .hr /"),      QString(".com .hr /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Cuba),
                         CountryInfoElement(QString("cu"),  QString("http:// https:// www. .com .cu /"),      QString(".com .cu /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Cyprus),
                         CountryInfoElement(QString("cy"),  QString("http:// https:// www. .com .cy /"),      QString(".com .cy /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::CzechRepublic),
                         CountryInfoElement(QString("cz"),  QString("http:// https:// www. .com .cz /"),      QString(".com .cz /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Denmark),
                         CountryInfoElement(QString("dk"),  QString("http:// https:// www. .com .dk /"),      QString(".com .dk /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Djibouti),
                         CountryInfoElement(QString("dj"),  QString("http:// https:// www. .com .dj /"),      QString(".com .dj /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Dominica),
                         CountryInfoElement(QString("dm"),  QString("http:// https:// www. .com .dm /"),      QString(".com .dm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::DominicanRepublic),
                         CountryInfoElement(QString("do"),  QString("http:// https:// www. .com .do /"),      QString(".com .do /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::EastTimor),
                         CountryInfoElement(QString("tl"),  QString("http:// https:// www. .com .tl /"),      QString(".com .tl /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Ecuador),
                         CountryInfoElement(QString("ec"),  QString("http:// https:// www. .com .ec /"),      QString(".com .ec /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Egypt),
                         CountryInfoElement(QString("eg"),  QString("http:// https:// www. .com .eg /"),      QString(".com .eg /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::ElSalvador),
                         CountryInfoElement(QString("sv"),  QString("http:// https:// www. .com .sv /"),      QString(".com .sv /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::EquatorialGuinea),
                         CountryInfoElement(QString("gq"),  QString("http:// https:// www. .com .gq /"),      QString(".com .gq /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Eritrea),
                         CountryInfoElement(QString("er"),  QString("http:// https:// www. .com .er /"),      QString(".com .er /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Estonia),
                         CountryInfoElement(QString("ee"),  QString("http:// https:// www. .com .ee /"),      QString(".com .ee /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Ethiopia),
                         CountryInfoElement(QString("et"),  QString("http:// https:// www. .com .et /"),      QString(".com .et /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::FalklandIslands),
                         CountryInfoElement(QString("fk"),  QString("http:// https:// www. .com .fk /"),      QString(".com .fk /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::FaroeIslands),
                         CountryInfoElement(QString("fo"),  QString("http:// https:// www. .com .fo /"),      QString(".com .fo /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Fiji),
                         CountryInfoElement(QString("fj"),  QString("http:// https:// www. .com .fj /"),      QString(".com .fj /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Finland),
                         CountryInfoElement(QString("fi"),  QString("http:// https:// www. .com .fi /"),      QString(".com .fi /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::France),
                         CountryInfoElement(QString("fr"),  QString("http:// https:// www. .com .fr /"),      QString(".com .fr /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Guernsey),
                         CountryInfoElement(QString("gg"),  QString("http:// https:// www. .com .co.gg /"),   QString(".com .co.gg /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::FrenchGuiana),
                         CountryInfoElement(QString("gf"),  QString("http:// https:// www. .com .gf /"),      QString(".com .gf /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::FrenchPolynesia),
                         CountryInfoElement(QString("pf"),  QString("http:// https:// www. .com .pf /"),      QString(".com .pf /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::FrenchSouthernTerritories),
                         CountryInfoElement(QString("tf"),  QString("http:// https:// www. .com .tf /"),      QString(".com .tf /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Gabon),
                         CountryInfoElement(QString("ga"),  QString("http:// https:// www. .com .ga /"),      QString(".com .ga /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Gambia),
                         CountryInfoElement(QString("gm"),  QString("http:// https:// www. .com .gm /"),      QString(".com .gm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Georgia),
                         CountryInfoElement(QString("ge"),  QString("http:// https:// www. .com .ge /"),      QString(".com .ge /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Germany),
                         CountryInfoElement(QString("de"),  QString("http:// https:// www. .com .de /"),      QString(".com .de /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Ghana),
                         CountryInfoElement(QString("gh"),  QString("http:// https:// www. .com .gh /"),      QString(".com .gh /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Gibraltar),
                         CountryInfoElement(QString("gi"),  QString("http:// https:// www. .com .gi /"),      QString(".com .gi /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Greece),
                         CountryInfoElement(QString("gr"),  QString("http:// https:// www. .com .gr /"),      QString(".com .gr /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Greenland),
                         CountryInfoElement(QString("gl"),  QString("http:// https:// www. .com .gl /"),      QString(".com .gl /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Grenada),
                         CountryInfoElement(QString("gd"),  QString("http:// https:// www. .com .gd /"),      QString(".com .gd /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Guadeloupe),
                         CountryInfoElement(QString("gp"),  QString("http:// https:// www. .com .gp /"),      QString(".com .gp /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Guam),
                         CountryInfoElement(QString("gu"),  QString("http:// https:// www. .com .gu /"),      QString(".com .gu /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Guatemala),
                         CountryInfoElement(QString("gt"),  QString("http:// https:// www. .com .gt /"),      QString(".com .gt /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Guinea),
                         CountryInfoElement(QString("gn"),  QString("http:// https:// www. .com .gn /"),      QString(".com .gn /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::GuineaBissau),
                         CountryInfoElement(QString("gw"),  QString("http:// https:// www. .com .gw /"),      QString(".com .gw /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Guyana),
                         CountryInfoElement(QString("gy"),  QString("http:// https:// www. .com .gy /"),      QString(".com .gy /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Haiti),
                         CountryInfoElement(QString("ht"),  QString("http:// https:// www. .com .ht /"),      QString(".com .ht /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::HeardAndMcDonaldIslands),
                         CountryInfoElement(QString("hm"),  QString("http:// https:// www. .com .hm /"),      QString(".com .hm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Honduras),
                         CountryInfoElement(QString("hn"),  QString("http:// https:// www. .com .hn /"),      QString(".com .hn /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::HongKong),
                         CountryInfoElement(QString("hk"),  QString("http:// https:// www. .com .hk /"),      QString(".com .hk /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Hungary),
                         CountryInfoElement(QString("hu"),  QString("http:// https:// www. .com .co.hu /"),   QString(".com .co.hu /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Iceland),
                         CountryInfoElement(QString("is"),  QString("http:// https:// www. .com .is /"),      QString(".com .is /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::India),
                         CountryInfoElement(QString("in"),  QString("http:// https:// www. .com .co.in /"),   QString(".com .co.in /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Indonesia),
                         CountryInfoElement(QString("id"),  QString("http:// https:// www. .com .co.id /"),   QString(".com .co.id /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Iran),
                         CountryInfoElement(QString("ir"),  QString("http:// https:// www. .com .co.ir /"),   QString(".com .co.ir /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Iraq),
                         CountryInfoElement(QString("iq"),  QString("http:// https:// www. .com .iq /"),      QString(".com .iq /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Ireland),
                         CountryInfoElement(QString("ie"),  QString("http:// https:// www. .com .ie /"),      QString(".com .ie /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Israel),
                         CountryInfoElement(QString("il"),  QString("http:// https:// www. .com .il /"),      QString(".com .il /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Italy),
                         CountryInfoElement(QString("it"),  QString("http:// https:// www. .com .it /"),      QString(".com .it /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Jamaica),
                         CountryInfoElement(QString("jm"),  QString("http:// https:// www. .com .jm /"),      QString(".com .jm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Japan),
                         CountryInfoElement(QString("jp"),  QString("http:// https:// www. .com .co.jp /"),   QString(".com .co.jp /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Jordan),
                         CountryInfoElement(QString("jo"),  QString("http:// https:// www. .com .jo /"),      QString(".com .jo /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Kazakhstan),
                         CountryInfoElement(QString("kz"),  QString("http:// https:// www. .com .kz /"),      QString(".com .kz /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Kenya),
                         CountryInfoElement(QString("ke"),  QString("http:// https:// www. .com .ke /"),      QString(".com .ke /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Kiribati),
                         CountryInfoElement(QString("ki"),  QString("http:// https:// www. .com .ki /"),      QString(".com .ki /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::NorthKorea),
                         CountryInfoElement(QString("kp"),  QString("http:// https:// www. .com .kp /"),      QString(".com .kp /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SouthKorea),
                         CountryInfoElement(QString("kr"),  QString("http:// www. .com .co.kr .net /"),       QString(".com .co.kr .net /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Kuwait),
                         CountryInfoElement(QString("kw"),  QString("http:// https:// www. .com .kw /"),      QString(".com .kw /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Kyrgyzstan),
                         CountryInfoElement(QString("kg"),  QString("http:// https:// www. .com .kg /"),      QString(".com .kg /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Laos),
                         CountryInfoElement(QString("la"),  QString("http:// https:// www. .com .la /"),      QString(".com .la /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Latvia),
                         CountryInfoElement(QString("lv"),  QString("http:// https:// www. .com .lv /"),      QString(".com .lv /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Lebanon),
                         CountryInfoElement(QString("lb"),  QString("http:// https:// www. .com .lb /"),      QString(".com .lb /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Lesotho),
                         CountryInfoElement(QString("ls"),  QString("http:// https:// www. .com .co.ls /"),   QString(".com .co.ls /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Liberia),
                         CountryInfoElement(QString("lr"),  QString("http:// https:// www. .com .lr /"),      QString(".com .lr /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Libya),
                         CountryInfoElement(QString("ly"),  QString("http:// https:// www. .com .ly /"),      QString(".com .ly /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Liechtenstein),
                         CountryInfoElement(QString("li"),  QString("http:// https:// www. .com .li /"),      QString(".com .li /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Lithuania),
                         CountryInfoElement(QString("lt"),  QString("http:// https:// www. .com .lt /"),      QString(".com .lt /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Luxembourg),
                         CountryInfoElement(QString("lu"),  QString("http:// https:// www. .com .lu /"),      QString(".com .lu /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Macau),
                         CountryInfoElement(QString("mo"),  QString("http:// https:// www. .com .mo /"),      QString(".com .mo /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Macedonia),
                         CountryInfoElement(QString("mk"),  QString("http:// https:// www. .com .mk /"),      QString(".com .mk /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Madagascar),
                         CountryInfoElement(QString("mg"),  QString("http:// https:// www. .com .mg /"),      QString(".com .mg /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Malawi),
                         CountryInfoElement(QString("mw"),  QString("http:// https:// www. .com .mw /"),      QString(".com .mw /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Malaysia),
                         CountryInfoElement(QString("my"),  QString("http:// https:// www. .com .my /"),      QString(".com .my /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Maldives),
                         CountryInfoElement(QString("mv"),  QString("http:// https:// www. .com .mv /"),      QString(".com .mv /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Mali),
                         CountryInfoElement(QString("ml"),  QString("http:// https:// www. .com .ml /"),      QString(".com .ml /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Malta),
                         CountryInfoElement(QString("mt"),  QString("http:// https:// www. .com .mt /"),      QString(".com .mt /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::MarshallIslands),
                         CountryInfoElement(QString("mh"),  QString("http:// https:// www. .com .mh /"),      QString(".com .mh /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Martinique),
                         CountryInfoElement(QString("mq"),  QString("http:// https:// www. .com .mq /"),      QString(".com .mq /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Mauritania),
                         CountryInfoElement(QString("mr"),  QString("http:// https:// www. .com .mr /"),      QString(".com .mr /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Mauritius),
                         CountryInfoElement(QString("mu"),  QString("http:// https:// www. .com .mu /"),      QString(".com .mu /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Mayotte),
                         CountryInfoElement(QString("yt"),  QString("http:// https:// www. .com .yt /"),      QString(".com .yt /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Mexico),
                         CountryInfoElement(QString("mx"),  QString("http:// https:// www. .com .mx /"),      QString(".com .mx /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Micronesia),
                         CountryInfoElement(QString("fm"),  QString("http:// https:// www. .com .fm /"),      QString(".com .fm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Moldova),
                         CountryInfoElement(QString("md"),  QString("http:// https:// www. .com .md /"),      QString(".com .md /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Monaco),
                         CountryInfoElement(QString("mc"),  QString("http:// https:// www. .com .mc /"),      QString(".com .mc /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Mongolia),
                         CountryInfoElement(QString("mn"),  QString("http:// https:// www. .com .mn /"),      QString(".com .mn /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Montserrat),
                         CountryInfoElement(QString("ms"),  QString("http:// https:// www. .com .ms /"),      QString(".com .ms /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Morocco),
                         CountryInfoElement(QString("ma"),  QString("http:// https:// www. .com .co.ma /"),   QString(".com .co.ma /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Mozambique),
                         CountryInfoElement(QString("mz"),  QString("http:// https:// www. .com .co.mz /"),   QString(".com .co.mz /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Myanmar),
                         CountryInfoElement(QString("mm"),  QString("http:// https:// www. .com .mm /"),      QString(".com .mm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Namibia),
                         CountryInfoElement(QString("na"),  QString("http:// https:// www. .com .na /"),      QString(".com .na /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::NauruCountry),
                         CountryInfoElement(QString("nr"),  QString("http:// https:// www. .com .nr /"),      QString(".com .nr /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Nepal),
                         CountryInfoElement(QString("np"),  QString("http:// https:// www. .com .np /"),      QString(".com .np /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Netherlands),
                         CountryInfoElement(QString("nl"),  QString("http:// https:// www. .com .nl /"),      QString(".com .nl /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::CuraSao),
                         CountryInfoElement(QString("cw"),  QString("http:// https:// www. .com .an /"),      QString(".com .an /")));  // many websites in CuraSao still use the former Netherlands Antilles's ccTLD, .an.
    s_countryHash.insert(QLocale::countryToString(QLocale::NewCaledonia),
                         CountryInfoElement(QString("nc"),  QString("http:// https:// www. .com .nc /"),      QString(".com .nc /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::NewZealand),
                         CountryInfoElement(QString("nz"),  QString("http:// https:// www. .com .nz /"),      QString(".com .nz /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Nicaragua),
                         CountryInfoElement(QString("ni"),  QString("http:// https:// www. .com .ni /"),      QString(".com .ni /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Niger),
                         CountryInfoElement(QString("ne"),  QString("http:// https:// www. .com .ne /"),      QString(".com .ne /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Nigeria),
                         CountryInfoElement(QString("ng"),  QString("http:// https:// www. .com .ng /"),      QString(".com .ng /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Niue),
                         CountryInfoElement(QString("nu"),  QString("http:// https:// www. .com .nu /"),      QString(".com .nu /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::NorfolkIsland),
                         CountryInfoElement(QString("nf"),  QString("http:// https:// www. .com .nf /"),      QString(".com .nf /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::NorthernMarianaIslands),
                         CountryInfoElement(QString("mp"),  QString("http:// https:// www. .com .mp /"),      QString(".com .mp /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Norway),
                         CountryInfoElement(QString("no"),  QString("http:// https:// www. .com .no /"),      QString(".com .no /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Oman),
                         CountryInfoElement(QString("om"),  QString("http:// https:// www. .com .om /"),      QString(".com .om /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Pakistan),
                         CountryInfoElement(QString("pk"),  QString("http:// https:// www. .com .pk /"),      QString(".com .pk /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Palau),
                         CountryInfoElement(QString("pw"),  QString("http:// https:// www. .com .co.pw /"),   QString(".com .co.pw /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::PalestinianTerritories),
                         CountryInfoElement(QString("ps"),  QString("http:// https:// www. .com .ps /"),      QString(".com .ps /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Panama),
                         CountryInfoElement(QString("pa"),  QString("http:// https:// www. .com .pa /"),      QString(".com .pa /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::PapuaNewGuinea),
                         CountryInfoElement(QString("pg"),  QString("http:// https:// www. .com .pg /"),      QString(".com .pg /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Paraguay),
                         CountryInfoElement(QString("py"),  QString("http:// https:// www. .com .py /"),      QString(".com .py /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Peru),
                         CountryInfoElement(QString("pe"),  QString("http:// https:// www. .com .pe /"),      QString(".com .pe /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Philippines),
                         CountryInfoElement(QString("ph"),  QString("http:// https:// www. .com .ph /"),      QString(".com .ph /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Pitcairn),
                         CountryInfoElement(QString("pn"),  QString("http:// https:// www. .com .co.pn /"),   QString(".com .co.pn /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Poland),
                         CountryInfoElement(QString("pl"),  QString("http:// https:// www. .com .pl /"),      QString(".com .pl /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Portugal),
                         CountryInfoElement(QString("pt"),  QString("http:// https:// www. .com .pt /"),      QString(".com .pt /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::PuertoRico),
                         CountryInfoElement(QString("pr"),  QString("http:// https:// www. .com .pr /"),      QString(".com .pr /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Qatar),
                         CountryInfoElement(QString("qa"),  QString("http:// https:// www. .com .qa /"),      QString(".com .qa /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Reunion),
                         CountryInfoElement(QString("re"),  QString("http:// https:// www. .com .re /"),      QString(".com .re /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Romania),
                         CountryInfoElement(QString("ro"),  QString("http:// https:// www. .com .ro /"),      QString(".com .ro /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Russia),
                         CountryInfoElement(QString("ru"),  QString("http:// https:// www. .com .ru /"),      QString(".com .ru /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Rwanda),
                         CountryInfoElement(QString("rw"),  QString("http:// https:// www. .com .rw /"),      QString(".com .rw /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SaintKittsAndNevis),
                         CountryInfoElement(QString("kn"),  QString("http:// https:// www. .com .kn /"),      QString(".com .kn /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SaintLucia),
                         CountryInfoElement(QString("lc"),  QString("http:// https:// www. .com .lc /"),      QString(".com .lc /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SaintVincentAndTheGrenadines),
                         CountryInfoElement(QString("vc"),  QString("http:// https:// www. .com .vc /"),      QString(".com .vc /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Samoa),
                         CountryInfoElement(QString("ws"),  QString("http:// https:// www. .com .ws /"),      QString(".com .ws /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SanMarino),
                         CountryInfoElement(QString("sm"),  QString("http:// https:// www. .com .sm /"),      QString(".com .sm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SaoTomeAndPrincipe),
                         CountryInfoElement(QString("st"),  QString("http:// https:// www. .com .st /"),      QString(".com .st /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SaudiArabia),
                         CountryInfoElement(QString("sa"),  QString("http:// https:// www. .com .sa /"),      QString(".com .sa /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Senegal),
                         CountryInfoElement(QString("sn"),  QString("http:// https:// www. .com .sn /"),      QString(".com .sn /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Seychelles),
                         CountryInfoElement(QString("sc"),  QString("http:// https:// www. .com .sc /"),      QString(".com .sc /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SierraLeone),
                         CountryInfoElement(QString("sl"),  QString("http:// https:// www. .com .sl /"),      QString(".com .sl /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Singapore),
                         CountryInfoElement(QString("sg"),  QString("http:// https:// www. .com .sg /"),      QString(".com .sg /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Slovakia),
                         CountryInfoElement(QString("sk"),  QString("http:// https:// www. .com .sk /"),      QString(".com .sk /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Slovenia),
                         CountryInfoElement(QString("si"),  QString("http:// https:// www. .com .si /"),      QString(".com .si /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SolomonIslands),
                         CountryInfoElement(QString("sb"),  QString("http:// https:// www. .com .sb /"),      QString(".com .sb /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Somalia),
                         CountryInfoElement(QString("so"),  QString("http:// https:// www. .com .so /"),      QString(".com .so /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SouthAfrica),
                         CountryInfoElement(QString("za"),  QString("http:// https:// www. .com .co.za /"),   QString(".com .co.za /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SouthGeorgiaAndTheSouthSandwichIslands),
                         CountryInfoElement(QString("gs"),  QString("http:// https:// www. .com .gs /"),      QString(".com .gs /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Spain),
                         CountryInfoElement(QString("es"),  QString("http:// https:// www. .com .es /"),      QString(".com .es /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SriLanka),
                         CountryInfoElement(QString("lk"),  QString("http:// https:// www. .com .lk /"),      QString(".com .lk /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SaintHelena),
                         CountryInfoElement(QString("sh"),  QString("http:// https:// www. .com .sh /"),      QString(".com .sh /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SaintPierreAndMiquelon),
                         CountryInfoElement(QString("pm"),  QString("http:// https:// www. .com .pm /"),      QString(".com .pm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Sudan),
                         CountryInfoElement(QString("sd"),  QString("http:// https:// www. .com .sd /"),      QString(".com .sd /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Suriname),
                         CountryInfoElement(QString("sr"),  QString("http:// https:// www. .com .sr /"),      QString(".com .sr /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SvalbardAndJanMayenIslands),
                         CountryInfoElement(QString("sj"),  QString("http:// https:// www. .com .no /"),      QString(".com .no /"))); // follow the ".no"
    s_countryHash.insert(QLocale::countryToString(QLocale::Swaziland),
                         CountryInfoElement(QString("sz"),  QString("http:// https:// www. .com .co.sz /"),   QString(".com .co.sz /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Sweden),
                         CountryInfoElement(QString("se"),  QString("http:// https:// www. .com .se /"),      QString(".com .se /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Switzerland),
                         CountryInfoElement(QString("ch"),  QString("http:// https:// www. .com .ch /"),      QString(".com .ch /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Syria),
                         CountryInfoElement(QString("sy"),  QString("http:// https:// www. .com .sy /"),      QString(".com .sy /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Taiwan),
                         CountryInfoElement(QString("tw"),  QString("http:// https:// www. .com .tw /"),      QString(".com .tw /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Tajikistan),
                         CountryInfoElement(QString("tj"),  QString("http:// https:// www. .com .tj /"),      QString(".com .tj /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Tanzania),
                         CountryInfoElement(QString("tz"),  QString("http:// https:// www. .com .co.tz /"),   QString(".com .co.tz /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Thailand),
                         CountryInfoElement(QString("th"),  QString("http:// https:// www. .com .co.th /"),   QString(".com .co.th /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Togo),
                         CountryInfoElement(QString("tg"),  QString("http:// https:// www. .com .tg /"),      QString(".com .tg /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Tokelau),
                         CountryInfoElement(QString("tk"),  QString("http:// https:// www. .com .tk /"),      QString(".com .tk /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Tonga),
                         CountryInfoElement(QString("to"),  QString("http:// https:// www. .com .to /"),      QString(".com .to /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::TrinidadAndTobago),
                         CountryInfoElement(QString("tt"),  QString("http:// https:// www. .com .tt /"),      QString(".com .tt /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Tunisia),
                         CountryInfoElement(QString("tn"),  QString("http:// https:// www. .com .tn /"),      QString(".com .tn /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Turkey),
                         CountryInfoElement(QString("tr"),  QString("http:// https:// www. .com .tr /"),      QString(".com .tr /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Turkmenistan),
                         CountryInfoElement(QString("tm"),  QString("http:// https:// www. .com .tm /"),      QString(".com .tm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::TurksAndCaicosIslands),
                         CountryInfoElement(QString("tc"),  QString("http:// https:// www. .com .tc /"),      QString(".com .tc /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Tuvalu),
                         CountryInfoElement(QString("tv"),  QString("http:// https:// www. .com .tv /"),      QString(".com .tv /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Uganda),
                         CountryInfoElement(QString("ug"),  QString("http:// https:// www. .com .ug /"),      QString(".com .ug /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Ukraine),
                         CountryInfoElement(QString("ua"),  QString("http:// https:// www. .com .ua /"),      QString(".com .ua /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::UnitedArabEmirates),
                         CountryInfoElement(QString("ae"),  QString("http:// https:// www. .com .co.ae /"),   QString(".com .co.ae /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::UnitedKingdom),
                         CountryInfoElement(QString("uk"),  QString("http:// https:// www. .com .uk /"),      QString(".com .uk /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::UnitedStates),
                         CountryInfoElement(QString("us"),  QString("http:// https:// www. .com .org /"),     QString(".com .org /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::UnitedStatesMinorOutlyingIslands),
                         CountryInfoElement(QString("us"),  QString("http:// https:// www. .com .org /"),     QString(".com .org /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Uruguay),
                         CountryInfoElement(QString("uy"),  QString("http:// https:// www. .com .uy /"),      QString(".com .uy /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Uzbekistan),
                         CountryInfoElement(QString("uz"),  QString("http:// https:// www. .com .uz /"),      QString(".com .uz /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Vanuatu),
                         CountryInfoElement(QString("vu"),  QString("http:// https:// www. .com .vu /"),      QString(".com .vu /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::VaticanCityState),
                         CountryInfoElement(QString("va"),  QString("http:// https:// www. .com .va /"),      QString(".com .va /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Venezuela),
                         CountryInfoElement(QString("ve"),  QString("http:// https:// www. .com .ve /"),      QString(".com .ve /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Vietnam),
                         CountryInfoElement(QString("vn"),  QString("http:// https:// www. .com .vn /"),      QString(".com .vn /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::BritishVirginIslands),
                         CountryInfoElement(QString("vg"),  QString("http:// https:// www. .com .vg /"),      QString(".com .vg /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::UnitedStatesVirginIslands),
                         CountryInfoElement(QString("vi"),  QString("http:// https:// www. .com .vi /"),      QString(".com .vi /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::WallisAndFutunaIslands),
                         CountryInfoElement(QString("wf"),  QString("http:// https:// www. .com .wf /"),      QString(".com .wf /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::WesternSahara),
                         CountryInfoElement(QString("eh"),  QString("http:// https:// www. .com .org /"),     QString(".com .org /")));  // no domains for "eh"
    s_countryHash.insert(QLocale::countryToString(QLocale::Yemen),
                         CountryInfoElement(QString("ye"),  QString("http:// https:// www. .com .ye /"),      QString(".com .ye /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::CanaryIslands),
                         CountryInfoElement(QString("es"),  QString("http:// https:// www. .com .es /"),      QString(".com .es /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Zambia),
                         CountryInfoElement(QString("zm"),  QString("http:// https:// www. .com .zm /"),      QString(".com .zm /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Zimbabwe),
                         CountryInfoElement(QString("zw"),  QString("http:// https:// www. .com .co.zw /"),   QString(".com .co.zw /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::ClippertonIsland),
                         CountryInfoElement(QString("pf"),  QString("http:// https:// www. .com .pf /"),      QString(".com .pf /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Montenegro),
                         CountryInfoElement(QString("me"),  QString("http:// https:// www. .com .co.me /"),   QString(".com .co.me /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Serbia),
                         CountryInfoElement(QString("rs"),  QString("http:// https:// www. .com .co.rs /"),   QString(".com .co.rs /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SaintBarthelemy),
                         CountryInfoElement(QString("gp"),  QString("http:// https:// www. .com .gp /"),      QString(".com .gp /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SaintMartin),
                         CountryInfoElement(QString("gp"),  QString("http:// https:// www. .com .gp /"),      QString(".com .gp /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::AscensionIsland),
                         CountryInfoElement(QString("ac"),  QString("http:// https:// www. .com .com.ac /"),  QString(".com .com.ac /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::AlandIslands),
                         CountryInfoElement(QString("ax"),  QString("http:// https:// www. .com .ax /"),      QString (".com .ax /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::IsleOfMan),
                         CountryInfoElement(QString("im"),  QString("http:// https:// www. .com .co.im /"),   QString(".com .co.im /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::Jersey),
                         CountryInfoElement(QString("je"),  QString("http:// https:// www. .com .co.je /"),   QString(".com .co.je /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SouthSudan),
                         CountryInfoElement(QString("ss"),  QString("http:// https:// www. .com .ss /"),      QString(".com .ss /")));
    s_countryHash.insert(QLocale::countryToString(QLocale::SintMaarten),
                         CountryInfoElement(QString("sx"),  QString("http:// https:// www. .com .sx /"),      QString(".com .sx /")));
    s_countryHash.squeeze();

    s_hash3166.insert(QString("KOR"), QLocale::SouthKorea);
    s_hash3166.insert(QString("USA"), QLocale::UnitedStates);
    s_hash3166.insert(QString("CAN"), QLocale::Canada);
    s_hash3166.insert(QString("MEX"), QLocale::Mexico);
    s_hash3166.insert(QString("HND"), QLocale::Honduras);
    s_hash3166.insert(QString("BRA"), QLocale::Brazil);
    s_hash3166.insert(QString("CHL"), QLocale::Chile);
    s_hash3166.insert(QString("PER"), QLocale::Peru);
    s_hash3166.insert(QString("ARG"), QLocale::Argentina);
    s_hash3166.insert(QString("ECU"), QLocale::Ecuador);
    s_hash3166.insert(QString("SWE"), QLocale::Sweden);
    s_hash3166.insert(QString("DNK"), QLocale::Denmark);
    s_hash3166.insert(QString("NOR"), QLocale::Norway);
    s_hash3166.insert(QString("FIN"), QLocale::Finland);
    s_hash3166.insert(QString("ALB"), QLocale::Albania);
    s_hash3166.insert(QString("AUT"), QLocale::Austria);
    s_hash3166.insert(QString("BLR"), QLocale::Belarus);
    s_hash3166.insert(QString("BEL"), QLocale::Belgium);
    s_hash3166.insert(QString("BIH"), QLocale::BosniaAndHerzegowina);
    s_hash3166.insert(QString("BGR"), QLocale::Bulgaria);
    s_hash3166.insert(QString("HRV"), QLocale::Croatia);
    s_hash3166.insert(QString("CZE"), QLocale::CzechRepublic);
    s_hash3166.insert(QString("EST"), QLocale::Estonia);
    s_hash3166.insert(QString("FRA"), QLocale::France);
    s_hash3166.insert(QString("DEU"), QLocale::Germany);
    s_hash3166.insert(QString("GRC"), QLocale::Greece);
    s_hash3166.insert(QString("HUN"), QLocale::Hungary);
    s_hash3166.insert(QString("IRL"), QLocale::Ireland);
    s_hash3166.insert(QString("ITA"), QLocale::Italy);
    s_hash3166.insert(QString("KAZ"), QLocale::Kazakhstan);
    s_hash3166.insert(QString("LVA"), QLocale::Latvia);
    s_hash3166.insert(QString("LTU"), QLocale::Lithuania);
    s_hash3166.insert(QString("LUX"), QLocale::Luxembourg);
    s_hash3166.insert(QString("MAR"), QLocale::Morocco);
    s_hash3166.insert(QString("NLD"), QLocale::Netherlands);
    s_hash3166.insert(QString("POL"), QLocale::Poland);
    s_hash3166.insert(QString("PRT"), QLocale::Portugal);
    s_hash3166.insert(QString("ROU"), QLocale::Romania);
    s_hash3166.insert(QString("RUS"), QLocale::Russia);
    s_hash3166.insert(QString("SRB"), QLocale::Serbia);
    s_hash3166.insert(QString("SVK"), QLocale::Slovakia);
    s_hash3166.insert(QString("SVN"), QLocale::Slovenia);
    s_hash3166.insert(QString("ESP"), QLocale::Spain);
    s_hash3166.insert(QString("CHE"), QLocale::Switzerland);
    s_hash3166.insert(QString("TUR"), QLocale::Turkey);
    s_hash3166.insert(QString("GBR"), QLocale::UnitedKingdom);
    s_hash3166.insert(QString("UKR"), QLocale::Ukraine);
    s_hash3166.insert(QString("CHN"), QLocale::China);
    s_hash3166.insert(QString("TWN"), QLocale::Taiwan);
    s_hash3166.insert(QString("COL"), QLocale::Colombia);
    s_hash3166.insert(QString("PAN"), QLocale::Panama);
    s_hash3166.insert(QString("ISR"), QLocale::Israel);
    s_hash3166.insert(QString("HKG"), QLocale::HongKong);
    s_hash3166.insert(QString("JPN"), QLocale::Japan);
    s_hash3166.insert(QString("AUS"), QLocale::Australia);
    s_hash3166.insert(QString("IND"), QLocale::India);
    s_hash3166.insert(QString("IDN"), QLocale::Indonesia);
    s_hash3166.insert(QString("MAL"), QLocale::Malaysia);
    s_hash3166.insert(QString("MMR"), QLocale::Myanmar);
    s_hash3166.insert(QString("NZL"), QLocale::NewZealand);
    s_hash3166.insert(QString("PHL"), QLocale::Philippines);
    s_hash3166.insert(QString("SGP"), QLocale::Singapore);
    s_hash3166.insert(QString("LKA"), QLocale::SriLanka);
    s_hash3166.insert(QString("THA"), QLocale::Thailand);
    s_hash3166.insert(QString("VNM"), QLocale::Vietnam);
    s_hash3166.insert(QString("DZA"), QLocale::Algeria);
    s_hash3166.insert(QString("CMR"), QLocale::Cameroon);
    s_hash3166.insert(QString("GHA"), QLocale::Ghana);
    s_hash3166.insert(QString("IRN"), QLocale::Iran);
    s_hash3166.insert(QString("IRQ"), QLocale::Iraq);
    s_hash3166.insert(QString("JOR"), QLocale::Jordan);
    s_hash3166.insert(QString("KEN"), QLocale::Kenya);
    s_hash3166.insert(QString("LBN"), QLocale::Lebanon);
    s_hash3166.insert(QString("LBY"), QLocale::Libya);
    s_hash3166.insert(QString("MWI"), QLocale::Malawi);
    s_hash3166.insert(QString("MUS"), QLocale::Mauritius);
    s_hash3166.insert(QString("NAM"), QLocale::Namibia);
    s_hash3166.insert(QString("NGA"), QLocale::Nigeria);
    s_hash3166.insert(QString("PAK"), QLocale::Pakistan);
    s_hash3166.insert(QString("SAU"), QLocale::SaudiArabia);
    s_hash3166.insert(QString("ZAF"), QLocale::SouthAfrica);
    s_hash3166.insert(QString("TUN"), QLocale::Tunisia);
    s_hash3166.insert(QString("UGA"), QLocale::Uganda);
    s_hash3166.insert(QString("ZMB"), QLocale::Zambia);
    s_hash3166.insert(QString("ZWE"), QLocale::Zimbabwe);
    s_hash3166.squeeze();
}
