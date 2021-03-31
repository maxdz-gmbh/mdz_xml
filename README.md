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

<p>- mdz_xml (ver. 0.1) is used as shared library (dll) in test-code<br>
- Rapid-XML (latest version 1.13), used from sources in test-code<br>
- TinyXML-2 (latest version on 23.03.2021), used from sources in text-code<br>
(only actual parsing time in Parse() function is measured for TinyXML-2)<br>
- MSXML 6.0 (6.30.18362.418), used via IXMLDOMDocument in test-code/64bit

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
