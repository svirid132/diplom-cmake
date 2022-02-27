#include "docx-data.h"
#include "handler-chart.h"

#include <QDebug>
#include <QXmlStreamReader>

HandlerChart::HandlerChart() :
    namePoint("")
{

}

QString handleAxis(const QList<float>& nums) {
    int count = nums.count();
    const QString num = "<c:pt idx=\"%1\"><c:v>%2</c:v></c:pt>";
    QString handleNums = "";
    for (int i = 0; i < nums.count(); ++i) {
        QString handleNum = num.arg(i).arg(nums.at(i));
        handleNums.append(handleNum);
    }
    const QString axis = "<c:numCache><c:formatCode>General</c:formatCode><c:ptCount val=\"%1\"/>%2</c:numCache>";
    QString handleStrAxis = axis.arg(count).arg(handleNums);

    return handleStrAxis;
}

QString handleStrPoint(const QString& str) {
    QString string = "<c15:dlblRangeCache><c:ptCount val=\"1\"/><c:pt idx=\"0\"><c:v>%1</c:v></c:pt></c15:dlblRangeCache>";
    QString handleStr = string.arg(str);

    return handleStr;
}

void HandlerChart::appendChart(QList<QPointF> chart, CHART_NUMBER chartNumber, const QString &namePoint)
{
    QList<float> xs;
    QList<float> ys;
    for (int i = 0; i < chart.length(); ++i) {
        float x = chart.at(i).x();
        float y = chart.at(i).y();
        xs.append(x);
        ys.append(y);
    }
    QString handleX = handleAxis(xs);
    QString handleY = handleAxis(ys);
    AxisChart axisChart;
    axisChart.x = handleX;
    axisChart.y = handleY;
    charts.insert(chartNumber, axisChart);

    if (namePoint != "") {
        this->namePoint = handleStrPoint(namePoint);
    }
}

void HandlerChart::setRawData(const QString &rawData)
{
    this->rawData = rawData;
}

//namepoint dlblRangeCache
//<c15:dlblRangeCache><c:ptCount val="1"/><c:pt idx="0"><c:v>НЕОПАСНО</c:v></c:pt></c15:dlblRangeCache>

//x,y
//<c:numCache><c:formatCode>General</c:formatCode><c:ptCount val="1"/><c:pt idx="0"><c:v>4.776</c:v></c:pt></c:numCache>


StartEnd rangeAxis(int start, QXmlStreamReader& xml) {
    bool end = false;
    StartEnd range = {start, 0};
    while(!end) {
        xml.readNext();
        if (xml.isEndElement() && (xml.name().toString() == "numCache")) {
            range.end = xml.characterOffset();
            end = true;
        }
    }

    return range;
}

StartEnd rangeStrPoint(int start, QXmlStreamReader& xml) {
    bool end = false;
    StartEnd range = {start, 0};
    while(!end) {
        xml.readNext();
        if (xml.isEndElement() && (xml.name().toString() == "dlblRangeCache")) {
            range.end = xml.characterOffset();
            end = true;
        }
    }

    return range;
}

QString HandlerChart::handleCharts()
{
    QXmlStreamReader xml(rawData);
    QList<StartEnd> rangeAxes;
    StartEnd rangeStr;

    while(!xml.atEnd()) {
        int offsetStart = xml.characterOffset();
        xml.readNext();
        if (xml.isStartElement() && xml.name().toString() == "numCache") {
            StartEnd range = rangeAxis(offsetStart, xml);
            rangeAxes.append(range);
        } else if (xml.isStartElement() && xml.name().toString() == "dlblRangeCache") {
            rangeStr = rangeStrPoint(offsetStart, xml);
        }
    }

    QString data = rawData;
    for(int i = rangeAxes.count() - 1; i > -1; --i) {

        //stringPoint
        if (i == 3) {
            data.remove(rangeStr.start, rangeStr.end - rangeStr.start);
            data.insert(rangeStr.start, namePoint);
        }

        CHART_NUMBER num;
        if (i == 0 || i == 1) {
            num = CHART_NUMBER::first;
        } else if (i == 2 || i == 3) {
            num = CHART_NUMBER::second;
        }

        StartEnd range = rangeAxes.at(i);
        switch (i % 2) {
        case 1: {
            QString y = charts[num].y;
            if (y == "") break;
            data.remove(range.start, range.end - range.start);
            data.insert(range.start, charts[num].y);
            break;
        }
        case 0: {
            QString x = charts[num].x;
            if (x == "") break;
            data.remove(range.start, range.end - range.start);
            data.insert(range.start, charts[num].x);
            break;
        }}
    }

    if (xml.hasError()) {
        qDebug() << "Ошибка чтения";
    }

    return data;
}
