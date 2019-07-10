#include "miodevice.h"
#include "ui_miodevice.h"
#include<QDataStream>
#include<QDebug>
miodevice::miodevice(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::miodevice)
{
    ui->setupUi(this);
}

miodevice::~miodevice()
{
    delete ui;
}

void miodevice::on_pushButton_load_clicked()
{
    QString curPath=QDir::currentPath();
    QString dlgfile=tr("select a file");
    QString filter=tr(" 文本文件(*.txt);;图片文件(*.jpg *.bmp);;所有文件(*.*)");
    QString afilename=QFileDialog::getOpenFileName(this,dlgfile,curPath,filter);
    /*
     * 多个文件：
     * QStringList fileList=QFileDialog::getOpenFileName(this,dlgfile,curPath,filter);
     * for(int i=0;i<fileList.count();i++)
     * std::cout<<fileList.at(i)
*/
  //  QCoreApplication::applicationDirPath()
   // QCoreApplication::applicationFilePath()
    if(!afilename.isEmpty())
    {
        this->path=afilename;
        ui->lineEdit->setText(afilename);
    }
}

void miodevice::on_pushButton_write_clicked()
{
    QFile mfile(this->path);
    if(!mfile.exists())
        return;
    if(mfile.open(QIODevice::Text|QIODevice::ReadWrite|QIODevice::Append))
        mfile.write(ui->textEdit->toPlainText().toLocal8Bit(),ui->textEdit->toPlainText().toLocal8Bit().length());
    mfile.close();
}

void miodevice::on_pushButton_read_clicked()
{
    QFile mfile(this->path);
    if(!mfile.exists())
        return;
    if(mfile.open(QIODevice::Text|QIODevice::ReadWrite))
    {
       // QByteArray t;
       // while(!mfile.atEnd())
         //   t=t+mfile.readAll();

     //ui->textEdit->append(QString::fromLocal8Bit(mfile.readAll()));
    }
    /*
    qDebug()<<QString::fromLocal8Bit(mfile.read(80))<<endl;
    bool isok;
  QByteArray sdata=mfile.read(1);
  int number=QString::fromLocal8Bit(sdata.toHex()).toInt(&isok,16);
  qDebug()<<QString::number(number);
     for(int i=0;i<12*number;i++)
        {
         sdata=mfile.read(2).toHex();
         qDebug()<<QString("%1").arg(sdata.toFloat());
     }
     mfile.close();
*/
}
/*
#include<iostream>
using namespace std;
bool ReadSTLFile(const char *cfilename)
{
	if (cfilename == NULL)
		return false;
 
    std::ifstream in(cfilename, std::ios::in);
	if (!in)
		return false;
 
	std::string headStr;
	getline(in, headStr, ' ');
	in.close();
 
	if (headStr.empty())
		return false;
 
	if (headStr[0] == 's')
	{
		cout << "ASCII File." << endl;
		ReadASCII(cfilename);
	}		
	else
	{
		cout << "Binary File." << endl;
		ReadBinary(cfilename);
	}
	return true;
}
 
bool ReadASCII(const char *cfilename)
{
	std::vector<float> coorX;
	std::vector<float> coorY;
	std::vector<float> coorZ;
 
	int i = 0, j = 0, cnt = 0, pCnt = 4;
	char a[100];
	char str[100];
	double x = 0, y = 0, z = 0;
 
	ifstream in;
	in.open(cfilename, ios::in);
	if (!in)
		return false;
	do
	{
		i = 0;
		cnt = 0;
		in.getline(a, 100, '\n');
		while (a[i] != '\0')
		{
			if (!islower((int)a[i]) && !isupper((int)a[i]) && a[i] != ' ')
				break;
			cnt++;
			i++;
		}
 
		while (a[cnt] != '\0')
		{
			str[j] = a[cnt];
			cnt++;
			j++;
		}
		str[j] = '\0';
		j = 0;
 
		if (sscanf(str, "%lf%lf%lf", &x, &y, &z) == 3)
		{
			coorX.push_back(x);
			coorY.push_back(y);
			coorZ.push_back(z);
		}
		pCnt++;
	} while (!in.eof());
 
	// 	cout << "******  ACSII FILES　******" << endl;
	// 	for (int i = 0; i < coorX.size();i++)
	// 	{
	// 		cout << coorX[i] << " : " << coorY[i] << " : " << coorZ[i] << endl;
	// 	}
 
	cout << coorX.size() / 3 << " triangles." << endl;
	return true;
}
 
bool ReadBinary(const char *cfilename)
{
	std::vector<float> coorX;
	std::vector<float> coorY;
	std::vector<float> coorZ;
	
	char str[80];
	ifstream in;
	
	in.open(cfilename, ios::in | ios::binary);
 
	if (!in)
		return false;
 
	in.read(str, 80);
 
	//number of triangles
	int unTriangles;
	in.read((char*)&unTriangles, sizeof(int));
 
	if (unTriangles == 0)
		return false;
 
	for (int i = 0; i < unTriangles; i++)
	{
		float coorXYZ[12];
		in.read((char*)coorXYZ, 12 * sizeof(float));
 
		for (int j = 1; j < 4; j++)
		{
			coorX.push_back(coorXYZ[j * 3]);
			coorY.push_back(coorXYZ[j * 3 + 1]);
			coorZ.push_back(coorXYZ[j * 3 + 2]);
		}
 
		in.read((char*)coorXYZ, 2);
	}
 
	in.close();
 
	cout << coorX.size() / 3 << " triangles." << endl;
	return true;
}
*/
