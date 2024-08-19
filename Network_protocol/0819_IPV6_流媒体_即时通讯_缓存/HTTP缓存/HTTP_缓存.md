####  缓存(Cache)

- Cache 的发音跟 Cash(现金) 一样: 

- 缓存：存储在临时存储器中的数据
- 缓存的目的：减少网络带宽消耗，降低网络延迟，提升用户体验
- 缓存位置：浏览器、CDN、代理服务器、负载均衡器、服务器

#### HTTP缓存

- HTTP缓存：HTTP缓存是指浏览器或其他客户端缓存HTTP响应数据，以减少网络带宽消耗，降低网络延迟，提升用户体验
- HTTP缓存的关键字：Cache-Control、Expires、Last-Modified、ETag

====================================================================

#### Pragma
作用: Pragma 头部是 HTTP/1.0 中引入的，用来控制缓存行为。
最常见的值是 Pragma: no-cache，它告诉客户端不要从缓存中取数据，而是直接从服务器获取最新的资源。
优先级: 在HTTP/1.1中，Pragma: no-cache的行为类似于 Cache-Control: no-cache，
但由于它是HTTP/1.0的遗留产物，现代浏览器一般优先考虑 Cache-Control。
然而，如果 Cache-Control 和 Pragma 都存在，
那么 Pragma 在HTTP/1.0客户端中可能会被优先执行。

#### Cache-Control

- Cache-Control 是 HTTP/1.1 中定义的缓存控制字段，用于控制缓存的行为(策略)
- Cache-Control 可以在请求头和响应头中使用
- Cache-Control 的常见取值：
  - no-storage：不缓存数据到本地
  - no-cache：允许缓存，但在使用缓存之前, 每次需要发请求给服务器询问缓存是否变化,再来决定如何使用缓存
  - private：只允许用户缓存数据到本地（浏览器缓存）
  - public：允许用户、代理服务器缓存数据到本地（CDN缓存）
  - max-age：缓存的最大有效期（单位：秒）(多长时间不过期)
  - s-maxage：缓存的最大有效期（单位：秒），仅适用于公共缓存
  - must-revalidate：缓存必须在有效期内重新验证
  - proxy-revalidate：缓存必须在有效期内重新验证，仅适用于公共缓存

#### 优先级: Pragma > Cache-Control > Expires > Last-Modified > ETag

#### Expires

- Expires 是 HTTP/1.0 中定义的缓存控制字段，用于指定缓存的过期时间(GMT格式时间)
- Expires 的值是一个 HTTP 日期，表示缓存的过期时间
- Expires 的优先级低于 Cache-Control 的 max-age 和 s-maxage
- 如果 Cache-Control 中没有 max-age 或 s-maxage，则 Expires 字段才会生效

#### Last-Modified

- Last-Modified 是 HTTP 响应头中的一个字段，用于表示服务器上资源的最后修改时间
- Last-Modified 的值是一个 HTTP 日期，表示资源的最后修改时间
- 当客户端请求资源时，服务器会返回资源的 Last-Modified 值
- 客户端可以将 Last-Modified 值保存在缓存中，并在下次请求时将 Last-Modified 值作为 If-Modified-Since 头部发送给服务器
- 服务器收到 If-Modified-Since 头部后，会与资源的最后修改时间进行比较
- 如果资源的最后修改时间与 If-Modified-Since 头部中的时间相同，则服务器返回 304 Not Modified 响应，表示资源未修改，客户端可以使用缓存中的资源
- 如果资源的最后修改时间与 If-Modified-Since 头部中的时间不同，则服务器返回 200 OK 响应，并返回资源的最新版本

#### ETag

- ETag 是 HTTP 响应头中的一个字段，用于表示资源内容的唯一标识符, 由服务器生成
- ETag 的值是一个字符串，可以是资源的哈希值、版本号等
- 当客户端请求资源时，服务器会返回资源的 ETag 值
- 客户端可以将 ETag 值保存在缓存中，并在下次请求时将 ETag 值作为 If-None-Match 头部发送给服务器
- 服务器收到 If-None-Match 头部后，会与资源的 ETag 值进行比较
- 如果资源的 ETag 值与 If-None-Match 头部中的值相同，则服务器返回 304 Not Modified 响应，表示资源未修改，客户端可以使用缓存中的资源
- 如果资源的 ETag 值与 If-None-Match 头部中的值不同，则服务器返回 200 OK 响应，并返回资源的最新版本

==========================================================================
==========================================================================

#### 缓存 -- 请求头
- If-None-Match  是一个 HTTP 请求头字段，主要用于缓存验证
它与服务器响应头中的 ETag（实体标签）配合使用，以确定客户端缓存的资源是否仍然有效。

- If-None-Match 的作用
当客户端向服务器发起一个请求时，如果它已经缓存了该资源的副本，并且之前服务器返回的响应中包含了 ETag 头部，客户端可以在后续请求中使用 If-None-Match 头部来发送这个 ETag 值。

服务器接收到这个请求后，会将 If-None-Match 中的 ETag 值与服务器上该资源的当前 ETag 进行比较：

如果 ETag 值相同（即资源没有更改）：服务器会返回一个 304 Not Modified 响应。这意味着客户端缓存的资源仍然有效，可以继续使用缓存版本，无需下载新的内容。
这有助于减少网络带宽消耗和提高响应速度。

如果 ETag 值不同（即资源已更改）：服务器会返回一个新的 200 OK 响应，并包含最新的资源内容和新的 ETag 值。
客户端将使用新的资源内容并更新缓存。


使用示例
假设客户端已经缓存了一个资源，其 ETag 值为 "abc123"，客户端的请求可能如下所示：
GET /some-resource HTTP/1.1
Host: www.example.com
If-None-Match: "abc123"

服务器检查资源的当前 ETag 值：

如果 ETag 仍然是 "abc123"，服务器返回：
HTTP/1.1 304 Not Modified

如果资源发生了变化，ETag 已更新为 "def456"，服务器返回：
HTTP/1.1 200 OK
ETag: "def456"
Content-Type: text/html
Content-Length: 1024

[新资源的内容]


- If-None-Match 的作用场景
缓存验证：通过减少不必要的资源下载，提高网络效率和响应速度。
带宽优化：避免传输已经缓存且未修改的资源内容，节省带宽。
数据一致性：确保客户端获取的资源是最新的，避免使用过期内容。
与 If-Modified-Since 的区别
If-None-Match 与 ETag 配合：用于精确验证资源内容是否发生变化。ETag 的精度比时间戳高，能够检测到即使文件内容有细微变化但时间戳未更新的情况。
If-Modified-Since 与 Last-Modified 配合：基于时间戳验证资源是否发生变化。对于不太关注资源微小变化的场景，If-Modified-Since 可能足够。


- If-Modified-Since 是一个 HTTP 请求头字段，用于基于时间戳的缓存验证。当客户端请求服务器上的某个资源时，如果它已经缓存了该资源并且知道资源的最后修改时间，客户端可以在请求中包含 If-Modified-Since 头部。服务器收到这个请求后，会检查资源自给定时间以来是否被修改。

- If-Modified-Since 的作用
If-Modified-Since 主要用于减少不必要的数据传输和提高响应效率。其工作机制如下：

客户端缓存资源：当客户端第一次请求资源时，服务器会返回资源内容，并在响应头中包含 Last-Modified 头部，指示资源的最后修改时间。

后续请求：当客户端再次请求相同资源时，可以在请求头中包含 If-Modified-Since，并将其值设置为之前获取到的 Last-Modified 值。

- 服务器处理：

如果资源自指定时间以来未修改：服务器会返回 304 Not Modified 响应，表示客户端可以使用缓存的资源版本，无需重新下载。这个响应不会包含资源的内容，从而节省带宽。
如果资源自指定时间以来已修改：服务器会返回 200 OK 响应，并包含更新后的资源内容。客户端应使用新内容并更新缓存。
使用示例
假设客户端第一次请求资源，服务器返回的响应如下：
HTTP/1.1 200 OK
Last-Modified: Mon, 18 Aug 2024 10:00:00 GMT
Content-Type: text/html
Content-Length: 1024

[资源的内容]

客户端随后发起的请求可能包含 If-Modified-Since 头部：
GET /some-resource HTTP/1.1
Host: www.example.com
If-Modified-Since: Mon, 18 Aug 2024 10:00:00 GMT

服务器检查资源的最后修改时间：

如果资源未修改，服务器返回：
HTTP/1.1 304 Not Modified

如果资源已修改，服务器返回：
HTTP/1.1 200 OK
Last-Modified: Tue, 19 Aug 2024 11:00:00 GMT
Content-Type: text/html
Content-Length: 2048

[新资源的内容]


适用场景
降低带宽消耗：通过避免传输未修改的资源内容，减少带宽使用。
提升性能：客户端可以更快地响应，因为 304 Not Modified 响应比完全传输资源内容的响应更小、更快。
保持数据一致性：确保客户端使用的是最新版本的资源，避免使用过时内容。

与 If-None-Match 的区别
If-Modified-Since：基于时间戳验证资源是否发生变化。依赖于 Last-Modified 头部，适合简单的时间戳比较，但可能无法检测到细微的资源变化（如同一秒内的多次修改）。
If-None-Match：基于 ETag 验证资源是否发生变化。ETag 提供了更高的精度，因为它是基于资源内容生成的唯一标识符，可以检测到任何微小的变化。

================================================================

#### Last-Modified vs ETag
Last-Modified 的缺陷

Last-Modified 和 ETag 是 HTTP 协议中用于缓存验证的两个重要机制，它们都有各自的优点和缺陷。在具体场景中，服务器可以根据需求选择使用其中一个或两个一起使用。

Last-Modified 的缺陷
虽然 Last-Modified 在缓存控制中很有用，但它有以下几个缺陷：

时间精度问题:

Last-Modified 只能精确到秒。
这意味着如果资源在同一秒内多次修改，Last-Modified 无法反映这些变化。
因此，使用 Last-Modified 进行缓存验证可能会导致客户端未能检测到一些较小的修改。

无法处理回滚的情况:

如果资源的内容被修改了，然后又被回滚到之前的版本，Last-Modified 时间将更新为最近的修改时间。
然而，内容实际上并没有改变。
这种情况下，客户端会认为资源已修改并重新下载，即使内容没有变化。
依赖服务器时钟:

Last-Modified 值由服务器的系统时钟生成。如果服务器时钟不准确或不同步，可能导致不正确的缓存验证。这可能会导致客户端使用过期的内容，或者频繁地重新下载内容。
不能精确检测内容相同但时间不同的资源:

Last-Modified 仅基于时间戳，而不考虑内容本身。如果资源的内容在两次修改中是完全相同的，但时间不同，Last-Modified 还是会改变，从而导致客户端误认为资源已经更新。
客户端和服务器时钟不同步:

如果客户端和服务器的时钟存在显著差异，Last-Modified 验证可能会出错，导致缓存命中的不一致。
ETag 的优势
相比之下，ETag 通过给资源生成一个唯一标识符（通常基于内容的哈希值或其他算法生成）来解决 Last-Modified 的上述缺陷。


ETag 的优点包括：
只要资源的内容没有变化, 就不会重复传输资源数据
只要资源的内容发生了变化, 就会返回最新的资源数据给客户端

精确的内容比较:

ETag 基于资源内容生成，能够精确检测到资源的任何变化，即使这些变化在时间上无法通过 Last-Modified 捕捉。
支持回滚检测:

即使资源被修改后回滚到之前的版本，由于 ETag 是基于内容生成的，因此回滚后的 ETag 会与之前的相同，避免不必要的重新下载。
独立于服务器时钟:

ETag 不依赖服务器时钟的精度或同步情况，因此在跨时区或时钟不同步的环境中表现更好。
Last-Modified 和 ETag 结合使用
由于 Last-Modified 和 ETag 各有优缺点，服务器通常会同时使用这两个机制来进行缓存控制：

客户端会首先发送 If-None-Match 请求，服务器根据 ETag 检查内容是否修改。如果未修改，返回 304 Not Modified。
如果服务器没有设置 ETag 或客户端不支持 ETag，则回退到 If-Modified-Since，根据 Last-Modified 进行缓存验证。
通过结合使用，服务器可以提供更健壮和灵活的缓存策略，既利用 ETag 的精确性，又兼顾 Last-Modified 的简单性和兼容性。

=============================================================





