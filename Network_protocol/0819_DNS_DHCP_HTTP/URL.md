URL（统一资源定位符，Uniform Resource Locator）是互联网中用于标识资源的位置和访问方法的标准化字符串。URL是我们访问网页、下载文件或请求API时使用的地址。它描述了资源的位置以及如何通过特定协议访问它。

URL的组成部分：
一个完整的URL通常由以下几部分组成：

协议（Scheme）：

定义：指定访问资源时使用的协议。
示例：http://、https://、ftp://、mailto:、file://
功能：告诉浏览器或客户端如何与资源进行通信。例如，http和https用于网页访问，ftp用于文件传输，mailto用于电子邮件地址。
用户名和密码（可选）：

定义：一些URL包含用于身份验证的用户名和密码。
示例：ftp://user:password@ftp.example.com
功能：在访问需要身份验证的资源时提供登录凭据。如今，这种方式不常见，且不推荐用于安全性考虑。

主机名（Host）：

定义：标识资源所在的服务器地址，可以是域名或IP地址。
示例：www.example.com、192.168.1.1
功能：指示要访问的服务器的域名或IP地址。

端口号（Port）（可选）：

定义：指定用于与服务器通信的端口号。
示例：:80、:443
功能：默认端口号通常被省略，如http的默认端口是80，https的默认端口是443。当服务不使用默认端口时，必须显式指定端口号。

路径（Path）：

定义：指向服务器上资源的具体位置。
示例：/index.html、/images/photo.jpg
功能：描述了资源在服务器上的路径结构，可以指向文件或目录。


查询字符串（Query String）（可选）：

定义：提供额外的参数，通常用于指定资源的某些条件或请求的输入数据。
示例：?id=123&sort=asc
功能：以键值对的形式提供参数，键值对之间用&分隔。查询字符串通常用于GET请求中传递参数。

片段标识符（Fragment）（可选）：

定义：指定资源内部的一个片段，通常用于跳转到网页的特定部分。
示例：#section2
功能：浏览器解析URL时，会将页面滚动到该片段标识符指定的位置。


URL的示例：
https://www.example.com:443/path/to/resource?id=123&sort=asc#section2

https：协议，表示使用安全的HTTP协议。
www.example.com：主机名，表示要访问的服务器的域名。
:443：端口号，表示使用HTTPS协议的默认端口。
/path/to/resource：路径，表示资源在服务器上的位置。
?id=123&sort=asc：查询字符串，提供了查询参数。
#section2：片段标识符，指向页面的特定部分。


URL的特点：
唯一性：每个URL都是唯一的，指向特定的资源位置。
可访问性：用户通过浏览器、FTP客户端、API请求等方式使用URL访问资源。
可嵌套：URL可以嵌入到HTML文档中，用于创建超链接、图像引用、样式表和脚本的加载等。


URL与URI的区别：
URI（统一资源标识符，Uniform Resource Identifier）：是一个更广泛的术语，指代能够标识某个资源的字符串。
URL是URI的一个子集，URI还包括URN（统一资源名称，Uniform Resource Name），它仅标识资源而不涉及访问方法。
URL（统一资源定位符，Uniform Resource Locator）：不仅标识资源的位置，还提供了访问该资源的方法（协议）。



