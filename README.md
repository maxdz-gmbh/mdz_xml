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

| Test  | mdz_xml_parse() | mdz_xml_parse | mdz_xml_parseWritable() | mdz_xml_parseWritable | Rapid-XML|TinyXML-2|MSXML 6.0|pugiXml|
| :---:| ---: | ---: | ---: | ---: | ---: | 
| **800 MB**| |||||
| speed,  μs| 1,151,826   |1,083,251|1,040,145|**885,727**|1,686,864|7,424,695|12,940,236|1,243,289
| memory, MB| 2605.3      |3397.6   |**2429.8**   |2504.1 |4530.5   |5477.5   |3428.5    |3298.5
| **1.5 GB** | |  | | |  |
| speed,  μs | 1,984,213| 1,918,416 |1,809,865 | **1,573,526**| 2,965,762 |12,958,705|22,529,768|2,181,464|
| memory, MB | 4600.0   | 5981.3    |**4294.2**| 4423.3       | 7951.3 | 9601.6      |6095.3    |5806.0   |
| **2.0 GB** | |  | | |  |
| speed,  μs | 3,115,848| 2,895,025 |2,702,707   | **2,378,931**| crash | crashes | 32,466,422|3,428,855|
| memory, MB | 6283.8   | 8195.9    | **5862.1** | 6039.7       |       |         |8279.7     |7911.0|
| **2.7 GB** | |  | | |  |
| speed,  μs | 3886709 | parse failed| 3576868    |**3,176,886** | crash| crash |43,521,423 |4,124,275|
| memory, MB | 8162.1  |             | **7626.9** | 7852.9       |      |       |10809.6    |10274.6|

"Load file - parse - unload data" test scenario:

| Test<br>speed, μs  | mdz_xml<br>(speed) | mdz_xml<br>(memory) | Rapid-XML|TinyXML-2|MSXML 6.0|
| :---:| ---: | ---: | ---: | ---: | ---: |
| **800 MB**| **1,715,889**   |1,857,110|6,517,744|9,241,000|17,759,569|
| **1.5 GB** | **3,303,318**| 3,404,751 |18,256,977 | 18,200,126| 31,622,254 |
| **2.1 GB** | **3,248,350**| 3,533,602 |crash | 12,404,694| 28,289,604 |
| **2.7 GB** | parse failed| **9,688,218** |crash | crash| 57,976,988 |
