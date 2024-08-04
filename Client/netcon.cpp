#include "netcon.h"
#include "ui_netcon.h"
#include "widget.h"

NetCon::NetCon(QWidget *parent, MyClientSocket *socket) :
    QWidget(parent),
    ui(new Ui::NetCon),
    cSocket(socket)
{
    ui->setupUi(this);

    QFile file(R"(C:\Users\21196\Desktop\QTnote_lv\20140702_xml\text.xml)");// 字面量
    if(file.open(QIODevice::ReadOnly) == false)
    {
        qDebug()<< "文件打开失败!\n";
    }
    auto Content = file.readAll();
    file.close();// 读完后关闭

    QString errorMsg; // 错误信息
    int line,column; // 行 列
    if(doc.setContent(Content, &errorMsg, &line, &column) == false)
    {
        qDebug() << "line : "<< line << "column : " << column << "errormsg : " << errorMsg << endl;
        return;// XML 解析失败，直接返回
    }
    qDebug()<<"xml解析成功!\n";


    // QDomNode --- 抽象xml节点(更高一层)
    // QDomElement --元素节点
    // QDomText  -- 文本节点
    // QDomAttr -- 节点属性
    // nodeName -- 节点名称
    // nodevalue -- 节点值
    // xml节点是不会拷贝的,与原始文档共享同一内存
    // doc 对象不释放，整棵树xml树就会存在

    QDomElement root = doc.documentElement();// 根节点
    ui->lineEdit_IP->setText(root.firstChildElement("ip").text());
    ui->lineEdit_PORT->setText(root.firstChildElement("port").text());

    // 遍历
//    for(auto node = root.firstChild(); node.isNull() == false; node = node.nextSibling())
//    {
//        qDebug()<<node.nodeName()<< " " << node.toElement().text() << endl;
//    }

    // 取出属性
    qDebug()<<root.firstChildElement("ip").attribute("名称")<<endl;

    connect(ui->Sure, &QPushButton::clicked, [this]()//
    {
        auto ip = ui->lineEdit_IP->text();//获取用户输入的 IP 和端口
        auto port = ui->lineEdit_PORT->text();
        // 修改 XML 文件中的 IP 和端口信息
        this->doc.documentElement().firstChildElement("ip").firstChild().setNodeValue(ip);
        this->doc.documentElement().firstChildElement("port").firstChild().setNodeValue(port);

        // 修改属性
        doc.documentElement().firstChildElement("ip").setAttribute("名称", "一级代理");
        QFile file(R"(C:\Users\21196\Desktop\QTnote_lv\20140702_xml\text.xml)");
        file.open(QIODevice::WriteOnly);// 写--记得写之前将原有xml先备份因为会修改
        file.write(doc.toByteArray());//将修改后的 XML 写入文件
        file.close();// 关闭

        emit connectionInfoChanged(ip, port.toInt()); // 发射信号
        this->close();

    });

    connect(ui->Cancel, &QPushButton::clicked, this, &NetCon::onCancelButtonClicked); // 连接取消按钮信号到槽函数

}

void NetCon::onCancelButtonClicked()
{
    this->close(); // 删除本窗口
}


NetCon::~NetCon()
{
    delete ui;
}
