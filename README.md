## Performance Comparison

Performance comparison tables give an idea about 'mdz_xml* parsing overall performance compared to some well-known alternatives.

Following tests are executed:

- parsing of ~800 MB large XML file<br>
http://dumps.wikimedia.your.org/wikidatawiki/20210320/wikidatawiki-20210320-stub-articles6.xml.gz

- parsing of ~1.5 GB large XML file<br>
http://dumps.wikimedia.your.org/wikidatawiki/20210320/wikidatawiki-20210320-stub-meta-current16.xml.gz

- parsing of ~2.1 GB large XML file<br>
http://dumps.wikimedia.your.org/commonswiki/20210320/commonswiki-20210320-pages-meta-current4.xml-p53620252p55120251.bz2

- parsing of ~2.7 GB large XML file<br>
http://dumps.wikimedia.your.org/wikidatawiki/20210320/wikidatawiki-20210320-stub-meta-current18.xml.gz

Parsing has been tested on Intel i5-6600 @ 3.30GHz (4 cores/4 threads), 16 GB RAM, Windows 10 (64-bit) OS.

- mdz_xml (ver. 0.1) is built in VC++ toolset v100/64bit and used as static library in test-code, built in VC++ toolset v100/64bit<br>
- Rapid-XML (latest version 1.13), used from sources in test-code, built in VC++ toolset v100/64bit<br>
- TinyXML-2 (latest version on 23.03.2021), used from sources in text-code, built in VC++ toolset v100/64bit<br>
(only actual parsing time in Parse() function is measured for TinyXML-2)<br>
- MSXML 6.0 (6.30.18362.418), used via IXMLDOMDocument in test-code, built in VC++ toolset v100/64bit

- times are taken in microseconds using QueryPerformanceCounter() in main execution thread<br>
- memory usage is taken after parsing finished, from Task-Manager/Processes tab for concrete process<br>

| Test  | mdz_xml (speed) | mdz_xml (memory) | Rapid-XML|TinyXML-2|MSXML 6.0|
| :---:| ---: | ---: | ---: | ---: | ---: |
| *800 MB*| |||||
| speed,  μs| 1,156,537   |1,266,299|1,693,287|7,303,490|13,327,359|
| memory, MB| 3759.4   |2967.0|4530.5|5477.5|3428.5|
| *1.5 GB* | |  | | |  |
| speed,  μs | 2,015,650| 2,224,795 |3,035,618 | 12,905,802| 22,664,047 |
| memory, MB | 6612.7| 5231.3 |7951.3 | 9601.6| 6095.3 |
| *2.1 GB* | |  | | |  |
| speed,  μs | 1,697,668| 2,036,900 |crash | 9,066,542| 22,111,194 |
| memory, MB | 5146.1| 4331.4 | | 6978.0| 6107.5 |
| *2.7 GB* | |  | | |  |
| speed,  μs | parse failed| 4,183,155 |crash | crash| 43,348,381 |
| memory, MB | | 9267.0 | | | 10810.6 |

