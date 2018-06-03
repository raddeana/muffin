html_template = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
</head>
<body>
{content}
</body>
</html>
"""

def get_content(url):
  """
  解析URL，获取需要的html内容
  :param url: 目标网址
  :return: html
  """
  html = get_one_page(url)
  soup = BeautifulSoup(html, 'html.parser')
  content = soup.find('div', attrs={'itemprop': 'articleBody'})
  html = html_template.format(content=content)
  return html
