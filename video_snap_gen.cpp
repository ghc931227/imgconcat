int headerheight = 70;  // 顶上留一部分高度用了绘制logo和文件信息
int interval = 4;  
int column_count = basecolumn_; 
int total_width = column_count * one_img_width + (column_count+1) * interval; 
int row_count = (imglist.size() + column_count-1 ) / column_count; 
int total_height = row_count * one_img_height + (row_count+1) * interval + headerheight;

int row_no = 0; 
int col_no = 0;
QImage totalImage(total_width, total_height, QImage::Format_ARGB32_Premultiplied);
totalImage.fill(qRgb(255, 255, 255));
QPainter imagePainter(&totalImage);
imagePainter.setRenderHint(QPainter::Antialiasing, true);
imagePainter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
imagePainter.setFont(QFont(tr("楷体"), 13, QFont::Bold));
QString titlename(tr("影片名："));
titlename.append(QString::fromStdString(cinfo.title.c_str()));
titlename.append(tr("\t格式："));
titlename.append(QString::fromStdString(cinfo.format_name));
imagePainter.drawText(150, 30, titlename);
std::ostringstream oss;
oss << "文件大小：" << cinfo.size / 1000000 << "MB\t视频尺寸：" 
    << cinfo.width << "x" << cinfo.height << "\t视频时长：";
QString info = QString::fromStdString(oss.str());
info.append(TimetoStr(cinfo.duration));
imagePainter.drawText(150, 55, info);

for (list<QImage>::const_iterator it = imglist.begin();
     it != imglist.end(); ++it)
{
    int img_x = col_no * one_img_width + (col_no+1) * interval;
    int img_y = row_no * one_img_height + (row_no+1) * interval + headerheight;

    imagePainter.drawImage(img_x, img_y, *it);

    col_no++;
    if ((col_no % column_count) == 0 )
    {
        row_no ++;
        col_no = 0;
    }
}

imagePainter.end();
totalImage.save(QString::fromStdString(outname));
