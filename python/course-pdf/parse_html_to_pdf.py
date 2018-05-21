def parse_html_to_pdf():
  """
  解析URL，获取html，保存成pdf文件
  :return: None
  """
  try:
    for chapter in chapter_info:
      ctitle = chapter['title']
      url = chapter['url']
      # 文件夹不存在则创建（多级目录）
      dir_name = os.path.join(os.path.dirname(__file__), 'gen', ctitle)
      if not os.path.exists(dir_name):
          os.makedirs(dir_name)

      html = get_content(url)

      padf_path = os.path.join(dir_name, ctitle + '.pdf')
      save_pdf(html, os.path.join(dir_name, ctitle + '.pdf'))

      children = chapter['child_chapters']
      if children:
        for child in children:
          html = get_content(child['url'])
          pdf_path = os.path.join(dir_name, child['title'] + '.pdf')
          save_pdf(html, pdf_path)

  except Exception as e:
    print(e)
