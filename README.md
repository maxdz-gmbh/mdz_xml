**NOTE:** All 0.x releases are kind of "alpha-versions" without expectations of interface backward-compatibility.

## Table of Contents
[mdz_xml Overview](#mdz_xml-Overview)<br>
[mdz_xml Advantages](#mdz_xml-Advantages)<br>
[Performance Comparison](#performance-comparison)<br>
[mdz_xml Usage](#mdz_xml-Usage)<br>
[Licensing info](#Licensing-info)<br>

## mdz_xml Overview
Wiki: [mdz_ansi Wiki]<br>
file: *"mdz_xml.h"*

Please take a look at *"mdz_xml.h"* file or [mdz_xml Wiki] site for detailed functions descriptions.

[mdz_xml Wiki]: https://github.com/maxdz-gmbh/mdz_xml/wiki/mdz_xml-overview

[mdz_xml] - is a very lightweight, versatile and speedy C  library for  parsing XML-documents, building DOM-structure and navigating it. The library is developed by [maxdz Software GmbH]. Source code of library is highly-portable, conforms to ANSI C 89/90 Standard.

Only shared/dynamically loaded libraries (*.so* and *.dll* files with import libraries) are available for evaluation testing purposes. Static libraries are covered by our commercial licenses.

**Linux** binaries are built against Linux Kernel 2.6.18 - and thus should be compatible with Debian (from ver. 4.0), Ubuntu (from ver. 8.04), Fedora (from ver. 9)

**FreeBSD** binaries - may be used from FreeBSD ver. 7.0

**Win32** binaries are built using Visual Studio Platform Toolset "v90", thus are compatible with Windows versions from Windows 2000.<br>
**Win64** binaries are built using Visual Studio Platform Toolset "v100", thus are compatible with Windows versions from Windows XP.<br>

**Android** x86/armeabi-v7a binaries - may be used from Android API level 16 ("Jelly Bean" ver. 4.1.x)<br>
**Android** x86_64/arm64-v8a binaries - may be used from Android API level 21 ("Lollipop" ver. 5.0)

**macOS** binaries - x86_64, from *MacOS X v10.6.0*

[mdz_xml]: https://github.com/maxdz-gmbh/mdz_xml
[maxdz Software GmbH]: https://maxdz.com/

## mdz_xml Advantages

**1. High portability:** the whole code conforms to ANSI C 89/90 Standard.

**2. Little dependencies:** basically *mdz_xml* functions are only dependend on standard C-library memory-management/access functions. It means you can use library in your code without any further dependencies except standard platform libraries/APIs.

**3. Very fast:** the parser is ca. 50% faster and needs ca. 40% less memory than pugiXml (which is considered as one of the fastest parsers overall). And is ca. 20 times faster than of "MSXML" from Microsoft. Please take a look at comparison tables below [Performance Comparison](#performance-comparison).

**4. Parsing of very large XML-documents:** basically, for 64-bit version the only limitation is your available RAM. Still the parser uses memory very effectively, thus parsing of very large files (we mean 2 GB large and bigger files here) is still possible using mdz_xml with a 50% less RAM-consumption than "pugiXML" or "MSXML" (which are very memory-effective too).

**5. Parse error position:** you are getting position of invalid (non-parced) character in XML-document if there is parse error.

**6. Flexibility:** you can parse read-only XML-documents. You can parse writable XML-documents even faster and with less memory-consumption than read-only parse. You can parse files - our file reading is very fast too.

**7. Navigation:** you can navigate through XML DOM-structure to collect necessary information from elements/children, attributes or texts.

**8. Control:** you can allow/disallow characters to be parsed in element names, attributes, texts, etc. Parser itself handles <?..?> instructions, <!--...--> comments, and mixed content

## Performance Comparison

Performance comparison tables give an idea about **mdz_xml** parsing overall performance compared to some well-known alternatives.

Following tests are executed:

<p>- parsing of ~800 MB large XML file<br>
http://dumps.wikimedia.your.org/wikidatawiki/20210320/wikidatawiki-20210320-stub-articles6.xml.gz

<p>- parsing of ~1.5 GB large XML file<br>
http://dumps.wikimedia.your.org/wikidatawiki/20210320/wikidatawiki-20210320-stub-meta-current16.xml.gz

<p>- parsing of ~2.0 GB large XML file<br>
http://dumps.wikimedia.your.org/enwiki/20210320/enwiki-20210320-stub-meta-current20.xml.gz

<p>- parsing of ~2.7 GB large XML file<br>
http://dumps.wikimedia.your.org/wikidatawiki/20210320/wikidatawiki-20210320-stub-meta-current18.xml.gz

Parsing has been tested on Intel i5-6600 @ 3.30GHz (4 cores/4 threads), 16 GB RAM, Windows 10 (64-bit) OS.<br>
Build using VC++, toolset v100/64bit.

<p>- mdz_xml (ver. 0.1) is used as shared library (dll)<br>
- Rapid-XML (latest version 1.13), used from sources<br>
- TinyXML-2 (latest version on 23.03.2021), used from sources<br>
(only actual parsing time in Parse() function is measured for TinyXML-2)<br>
- MSXML 6.0 (6.30.18362.418), used via IXMLDOMDocument interface<br>
- pugiXml (latest version on 23.03.2021), used from sources

<p>- times are taken in microseconds using QueryPerformanceCounter() in main execution thread<br>
- memory usage is taken after parsing finished, from Task-Manager/Processes tab for concrete process<br>

Raw parse speed:

| Test  | mdz_xml_<br>parse() | mdz_xml_<br>parseWritable() | Rapid-XML|TinyXML-2|MSXML 6.0|pugiXml|
| :---: | ---:               | ---:                        | ---:       | ---:           | ---:            | ---:    |
| **800 MB**|                |                             |            |                 |            |          |
| speed,  μs| 965,468       |**830,137**               |1,686,864     |7,424,695     |12,940,236     |1,243,289 |
| memory, MB| 2028.4       |**1810.4**                  |4530.5       |5477.5       |3428.5        |3298.5 |
| **1.5 GB** |             |                           |              |             |                 |   |
| speed,  μs | 1,686,615   | **1,451,198**           | 2,965,762     |12,958,705    |22,529,768     |2,181,464|
| memory, MB | 3594.8      | **3214.9**             | 7951.3          | 9601.6      |6095.3        |5806.0   |
| **2.0 GB** |            |                         |                 |             |              |    |
| speed,  μs |  2,463,885 | **2,091,761**          |  crash          | crash      | 32,466,422   |3,428,855|
| memory, MB |   4892.3    | **4367.6**            |              |              |8279.7     |7911.0|
| **2.7 GB** |            |                       |                  |              |         |     |
| speed,  μs | 3,148,216| **2,682,474**           | crash           | crash        |43,521,423 |4,124,275|
| memory, MB | 6403.0  |  **5738.1**              |                 |              |10809.6    |10274.6|

"Load file - parse - unload data" test scenario:

| Test<br>speed, μs  | mdz_xml_<br>parseFile() | Rapid-XML|TinyXML-2|MSXML 6.0|pugiXml|
| :---:              | ---:                    | ---:      | ---:    | ---:    | ---: |
| **800 MB**         | **1,373,711**          |6,586,134   |9,278,020|16,457,514|1,899,272|
| **1.5 GB**        |  **2,439,384**          |16,474,472 | 16,493,514| 29,422,628 |3,515,159|
| **2.0 GB**        | **3,388,064**          |crash | crash| 43,360,017 |5,411,959|
| **2.7 GB**        | **4,406,550**          |crash | crash| 58,679,884 |9,551,191|
