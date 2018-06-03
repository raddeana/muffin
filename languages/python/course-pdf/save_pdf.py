def save_pdf(html, filename):
  """
  把所有html文件保存到pdf文件
  :param html:  html内容
  :param file_name: pdf文件名
  :return:
  """
  options = {
    'page-size': 'Letter',
    'margin-top': '0.75in',
    'margin-right': '0.75in',
    'margin-bottom': '0.75in',
    'margin-left': '0.75in',
    'encoding': "UTF-8",
    'custom-header': [
      ('Accept-Encoding', 'gzip')
    ],
    'cookie': [
      ('cookie-name1', 'cookie-value1'),
      ('cookie-name2', 'cookie-value2'),
    ],
    'outline-depth': 10,
  }

  pdfkit.from_string(html, filename, options=options)
