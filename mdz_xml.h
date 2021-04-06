/**
 * \ingroup mdz_xml library
 *
 * \author maxdz Software GmbH
 *
 * \par license
 * This file is subject to the terms and conditions defined in file 'LICENSE.txt', which is part of this source code package.
 *
 * \par description
 * mdz_xml is a library for parsing of XML-documents and creating DOM-structure
 *
 * Parser processes only ASCII/ANSI single-byte XML-documents. There are following limitations currently:
 *
 * - "Process Instructions" (instructions inside <? ... ?>) - are parsed but not processed and not inserted in DOM
 * - Comments (XML-code inside <!-- ... -->) - is parsed but not processed and not inserted in DOM
 * - Mixed content is supported
 *
 * - Following characters are treated as space-characters: '\n' (aka LF, code 0x0a), '\r' (aka CR, code 0x0d), '\t' (aka TAB, code 0x09), ' ' (aka SPACE, code 0x20)
 *
 * - Element name may start with following characters: ':', '_', [A..Z], [a..z]
 * - Element name may contain following characters: ':', '_', '-', '.', [A..Z], [a..z], [0..9]
 * - Restrictions to element name also apply to attribute name
 *
 * - Element text may contain every ANSI/ASCII character except: 0 ('\0', code 0x00) and '<'
 * - Restrictions to element text also apply to attribute value
 *
 * - CDATA Sections are not parsed and not processed (parsing error will be returned)
 *
 * - Whitespaces in element text/attribute value are preserved
 *
 * \par portability
 * Source code of library conforms to ANSI C 89/90 Standard.
 *
 * \version 0.1
 *
 * \date 2021-04
 *
 */

#ifndef MDZ_XML_H
#define MDZ_XML_H

#include "mdz_types.h"

enum mdz_xml_text_type
{
  /**
   * Space letter. By default '\n' (aka LF, code 0x0a), '\r' (aka CR, code 0x0d), '\t' (aka TAB, code 0x09), ' ' (aka SPACE, code 0x20)
   */
  MDZ_XML_SPACE = 0,

  /**
   * Start letter of element name. By default ':', '_', [A..Z], [a..z] are allowed
   */
  MDZ_XML_ELEMENT_NAME_START = 1,

  /**
   * Non-start letter of element name. By default ':', '_', '-', '.', [A..Z], [a..z], [0..9] are allowed
   */
  MDZ_XML_ELEMENT_NAME_NON_START = 2,

  /**
   * Start letter of attribute name. By default ':', '_', [A..Z], [a..z] are allowed
   */
  MDZ_XML_ATTRIBUTE_NAME_START = 3,

  /**
   * Non-start letter of attribute name. By default ':', '_', '-', '.', [A..Z], [a..z], [0..9] are allowed
   */
  MDZ_XML_ATTRIBUTE_NAME_NON_START = 4,

  /**
   * Element text letter. By default allowed everything except 0 ('\0', code 0x00) and '<'
   */
  MDZ_XML_ELEMENT_TEXT = 5,

  /**
   * Attribute value letter letter. By default allowed everything except 0 ('\0', code 0x00)
   */
  MDZ_XML_ATTRIBUTE_VALUE = 6
};

enum mdz_xml_error
{
  /**
   * No error
   */
  MDZ_XML_ERROR_NONE = 0,

  /**
  * Invalid license
  */
  MDZ_XML_ERROR_LICENSE = 1,

  /**
   * Invalid text param
   */
  MDZ_XML_ERROR_PARAM = 2,

  /**
   * Memory operation failed
   */
  MDZ_XML_ERROR_MEMORY = 3,

  /**
   * File operation failed
   */
  MDZ_XML_ERROR_FILE = 4,

  /**
   * Parse error
   */
  MDZ_XML_ERROR_PARSE = 5,

  /**
   * Invalid element
   */
  MDZ_XML_ERROR_ELEMENT = 6,

  /**
   * Invalid attribute index
   */
  MDZ_XML_ERROR_INDEX = 7
};

/**
 * Handle of XML attribute
 */
struct mdz_XmlAttribute
{
  /**
   * Pointer to attribute name
   */
  const char* m_pcName;

  /**
   * Attribute name length
   */
  size_t m_nNameLength;

  /**
   * Pointer to attribute value. NULL if value is empty
   */
  const char* m_pcValue;

  /**
   * Attribute value length
   */
  size_t m_nValueLength;
};

/**
 * Handle of XML element
 */
struct mdz_XmlElement
{
  /**
  * Pointer to element/text text
  */
  const char* m_pcText;

  /**
  * Element text/text length
  */
  size_t m_nTextLength;

  /**
   * Pointer to element name. This element is Text (in XML with mixed content) if m_pcName is NULL
   */
  const char* m_pcName;

  /**
   * Element name length. This element is Text (in XML with mixed content) if m_nNameLength is 0
   */
  size_t m_nNameLength;

  /**
   * Number of attributes. Always 0 if this element is Text (in XML with mixed content)
   */
  size_t m_nAttributes;

  /**
   * Pointer to the first child in children list. Always NULL if this element is Text (in XML with mixed content).
   * If not NULL, m_pFirstChild may be used as pWhereElement in mdz_xml_getElement() to retrieve first child of this element
   */
  const void* m_pFirstChild;

  /**
   * Pointer to the next element or text (for mixed content). NULL if there is no next element or text.
   * If not NULL, m_pNext may be used as pWhereElement in mdz_xml_getElement() to retrieve next element after this element in children list
   */
  const void* m_pNext;

  /**
   * Pointer to the internal element. 
   * m_pThis should not be NULL and may be used as pWhereElement in mdz_xml_getElement() and mdz_xml_getAttribute()
   */
  const void* m_pThis;
};

/**
 * Handle of XML-parser instance
 */
struct mdz_Xml
{
  /**
   * Error position in XML-text during parse. SIZE_MAX if parsing has not been started/succeeded.
   */
  size_t m_nErrorPos;

  /**
   * Error code if operation failed or there are some inconsistences.
   */
  size_t m_enErrorCode;
};

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \defgroup Library init/uninit functions
 */

/**
  * Initializes ansi library. This function should be called before any other function of the library.
  * \param pFirstNameHash - user first name hash code
  * \param pLastNameHash - user last name hash code
  * \param pEmailHash - user e-mail hash code
  * \param pLicenseHash - license hash code
  * \return:
  * mdz_true - if the initialization has succeed, otherwise false
  */
mdz_bool mdz_xml_init(const uint32_t* pFirstNameHash, const uint32_t* pLastNameHash, const uint32_t* pEmailHash, const uint32_t* pLicenseHash);

/**
 * Un-initializes ansi library and frees corresponding memory allocations.
 */
void mdz_xml_uninit(void);

/**
 * \defgroup Parser create/destroy functions
 */

/**
 * Create XML-parser instance.
 * \return:
 * NULL   - if library is not initialized with mdz_xml_init() call
 * NULL   - if memory allocation failed
 * Result - pointer to instance for use in other mdz_xml functions
 */
struct mdz_Xml* mdz_xml_create(void);

/**
 * Destroy XML-parser instance, including underlying data. After destroying, pointer to the instance is set to NULL.
 * \param ppXml - pointer to pointer to XML_parser instance returned by mdz_xml_create()
 */
void mdz_xml_destroy(struct mdz_Xml** ppXml);

/**
 * \defgroup Parse functions
 */

/**
 * Read-only parsing XML-document under pcText with length nTextLength. After successful parsing, DOM-structure will be built with a root at mdz_Xml.m_pRootElement.
 * \param pXml - pointer to XML-parser instance returned by mdz_xml_create()
 * \param pcText - XML-document to parce (single-bytes string)
 * \param nTextLength - length of XML-document to parce in bytes
 * \param bTrimSpaces - if leading/trail spaces in element text should be trimmed/deleted (makes DOM-structure in-memory size smaller)
 * \return:
 * mdz_false - if pXml == NULL
 * mdz_false - if license is invalid/expired (MDZ_XML_ERROR_LICENSE)
 * mdz_false - if pcText is NULL or empty or nTextLength is too small (MDZ_XML_ERROR_PARAM)
 * mdz_false - if there are memory-allocation problems (MDZ_XML_ERROR_MEMORY)
 * mdz_false - if there are parsing problems (MDZ_XML_ERROR_PARSE). In shis case mdz_Xml.m_nErrorPos contains position of unexpected/erroneous character in XML-document
 * mdz_true  - parsing succeeded
 */
mdz_bool mdz_xml_parse(const struct mdz_Xml* pXml, const char* pcText, size_t nTextLength, mdz_bool bTrimSpaces);

/**
 * Writable parsing XML-document under pcText with length nTextLength. During this parse XML-document can be modified (without losing XML-information), to significantly decrease in-memory size of DOM-structure comparing to mdz_xml_parse() result.
 * \param pXml - pointer to XML-parser instance returned by mdz_xml_create()
 * \param pcText - XML-document to parce (single-bytes string)
 * \param nTextLength - length of XML-document to parce in bytes
 * \param bTrimSpaces - if leading/trail spaces in element text should be trimmed/deleted (makes DOM-structure in-memory size smaller)
 * \return:
 * mdz_false - if pXml == NULL
 * mdz_false - if license is invalid/expired (MDZ_XML_ERROR_LICENSE)
 * mdz_false - if pcText is NULL or empty or nTextLength is too small (MDZ_XML_ERROR_PARAM)
 * mdz_false - if there are memory-allocation problems (MDZ_XML_ERROR_MEMORY)
 * mdz_false - if there are parsing problems (MDZ_XML_ERROR_PARSE). In shis case mdz_Xml.m_nErrorPos contains position of unexpected/erroneous character in XML-document
 * mdz_true  - parsing succeeded
 */
mdz_bool mdz_xml_parseWritable(const struct mdz_Xml* pXml, char* pcText, size_t nTextLength, mdz_bool bTrimSpaces);

/**
 * Reads from file and makes writable parsing of XML-document.
 * \param pXml - pointer to XML-parser instance returned by mdz_xml_create()
 * \param pcFileName - XML-document filename, including path. File-content will be treated as a single-bytes string
 * \param bTrimSpaces - if leading/trail spaces in element text should be trimmed/deleted (makes DOM-structure in-memory size smaller)
 * \return:
 * mdz_false - if pXml == NULL
 * mdz_false - if license is invalid/expired (MDZ_XML_ERROR_LICENSE)
 * mdz_false - if pcFileName is NULL or empty (MDZ_XML_ERROR_PARAM)
 * mdz_false - if file reading problems (MDZ_XML_ERROR_FILE)
 * mdz_false - if there are memory-allocation problems (MDZ_XML_ERROR_MEMORY)
 * mdz_false - if there are parsing problems (MDZ_XML_ERROR_PARSE). In shis case mdz_Xml.m_nErrorPos contains position of unexpected/erroneous character in XML-document
 * mdz_true  - parsing succeeded
 */
mdz_bool mdz_xml_parseFile(const struct mdz_Xml* pXml, const char* pcFileName, mdz_bool bTrimSpaces);

/**
 * \defgroup Service functions
 */

/**
 * Allow/disallow letter cLetter to be used in text, defined by enTextType. Please note: there are no checks on letters - thus invalid settings (like allowing '<' in element name) may break parsing functionality.
 * This function is applied to global settings and used by all parser instances.
 * \param enTextType - text type for allowing/disallowing
 * \param cLetter - letter to allow/disallow
 * \param bAllow - mdz_false to disallow, otherwise allow
 * \return:
 * mdz_false - if enTextType is out of range
 * mdz_true  - setting succeeded
 */
mdz_bool mdz_xml_allowLetter(enum mdz_xml_text_type enTextType, unsigned char cLetter, mdz_bool bAllow);

/**
 * Check if the letter cLetter is allowed to be used in text, defined by enTextType.
 * \param enTextType - text type for allowing/disallowing
 * \param cLetter - letter to allow/disallow
 * \return:
 * mdz_false - if enTextType is out of range or the letter is disallowed
 * mdz_true  - letter is allowed
 */
mdz_bool mdz_xml_isAllowedLetter(enum mdz_xml_text_type enTextType, unsigned char cLetter);

/**
 * \defgroup Navigation functions
 */

/**
 * Get Root-Element of parser. Root-Element always exists after successful parsing and includes root-element of XML-document as a child, or multiple elements as children (if XML-document contains multiple roots).
 * \param pXml - pointer to XML-parser instance returned by mdz_xml_create()
 * \param pRootElement - where Root-Element data should be written
 * \return:
 * mdz_false - if pXml == NULL
 * mdz_false - if license is invalid/expired (MDZ_XML_ERROR_LICENSE)
 * mdz_false - if pRootElement is NULL (MDZ_XML_ERROR_PARAM)
 * mdz_false - if last parsing failed (MDZ_XML_ERROR_PARSE)
 * mdz_true  - operation succeeded
 */
mdz_bool mdz_xml_getRootElement(const struct mdz_Xml* pXml, struct mdz_XmlElement* pRootElement);

/**
 * Get Element (or Text for XML with mixed-content) from parser.
 * \param pXml - pointer to XML-parser instance returned by mdz_xml_create()
 * \param pWhereElement - pointer to Element (or Text) to get. Use Element.m_pFirstChild for retrieving the first element in children list, or Element.m_pNext for retrieving the next element in list
 * \param pElement - where Element (or Text) data should be written
 * \return:
 * mdz_false - if pXml == NULL
 * mdz_false - if license is invalid/expired (MDZ_XML_ERROR_LICENSE)
 * mdz_false - if pWhereElement is NULL or pElement is NULL (MDZ_XML_ERROR_PARAM)
 * mdz_false - if last parsing failed (MDZ_XML_ERROR_PARSE)
 * mdz_false - if pWhereElement is invalid (MDZ_XML_ERROR_ELEMENT)
 * mdz_true  - operation succeeded
 */
mdz_bool mdz_xml_getElement(const struct mdz_Xml* pXml, const void* pWhereElement, struct mdz_XmlElement* pElement);

/**
 * Get element attribute from parser.
 * \param pXml - pointer to XML-parser instance returned by mdz_xml_create()
 * \param pWhereElement - pointer to Element (or Text) to get attribute for. Use Element.m_pThis for retrieving attribute of element
 * \param nAttributeIndex - 0-based index of attribute to get
 * \param pAttribute - where attribute data should be written
 * \return:
 * mdz_false - if pXml == NULL
 * mdz_false - if license is invalid/expired (MDZ_XML_ERROR_LICENSE)
 * mdz_false - if pWhereElement is NULL or pAttribute is NULL (MDZ_XML_ERROR_PARAM)
 * mdz_false - if last parsing failed (MDZ_XML_ERROR_PARSE)
 * mdz_false - if pWhereElement is invalid (MDZ_XML_ERROR_ELEMENT)
 * mdz_false - if nAttributeIndex is out of attributes range (MDZ_XML_ERROR_INDEX)
 * mdz_false - if there is some memory-management problem (MDZ_XML_ERROR_MEMORY)
 * mdz_true  - operation succeeded
 */
mdz_bool mdz_xml_getAttribute(struct mdz_Xml* pXml, const void* pWhereElement, size_t nAttributeIndex, struct mdz_XmlAttribute* pAttribute);

#ifdef __cplusplus
}
#endif

#endif
