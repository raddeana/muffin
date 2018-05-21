# 全局变量
base_url = 'http://python3-cookbook.readthedocs.io/zh_CN/latest/'
book_name = ''
chapter_info = []

def parse_title_and_url(html):
  """
  解析全部章节的标题和url
  :param html: 需要解析的网页内容
  :return None
  """
  soup = BeautifulSoup(html, 'html.parser')

  # 获取书名
  book_name = soup.find('div', class_='wy-side-nav-search').a.text
  menu = soup.find_all('div', class_='section')
  chapters = menu[0].div.ul.find_all('li', class_='toctree-l1')
  for chapter in chapters:
    info = {}
    # 获取一级标题和url
    # 标题中含有'/'和'*'会保存失败
    info['title'] = chapter.a.text.replace('/', '').replace('*', '')
    info['url'] = base_url + chapter.a.get('href')
    info['child_chapters'] = []

    # 获取二级标题和url
    if chapter.ul is not None:
      child_chapters = chapter.ul.find_all('li')
      for child in child_chapters:
        url = child.a.get('href')
        # 如果在url中存在'#'，则此url为页面内链接，不会跳转到其他页面
        # 所以不需要保存
        if '#' not in url:
          info['child_chapters'].append({
            'title': child.a.text.replace('/', '').replace('*', ''),
            'url': base_url + child.a.get('href'),
          })

    chapter_info.append(info)
