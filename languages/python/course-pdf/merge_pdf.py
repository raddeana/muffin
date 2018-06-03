from PyPDF2 import PdfFileReader, PdfFileWriter

def merge_pdf(infnList, outfn):
  """
  合并pdf
  :param infnList: 要合并的PDF文件路径列表
  :param outfn: 保存的PDF文件名
  :return: None
  """
  pagenum = 0
  pdf_output = PdfFileWriter()

  for pdf in infnList:
    # 先合并一级目录的内容
    first_level_title = pdf['title']
    dir_name = os.path.join(os.path.dirname(
        __file__), 'gen', first_level_title)
    padf_path = os.path.join(dir_name, first_level_title + '.pdf')

    pdf_input = PdfFileReader(open(padf_path, 'rb'))
    # 获取 pdf 共用多少页
    page_count = pdf_input.getNumPages()
    for i in range(page_count):
        pdf_output.addPage(pdf_input.getPage(i))

    # 添加书签
    parent_bookmark = pdf_output.addBookmark(
        first_level_title, pagenum=pagenum)

    # 页数增加
    pagenum += page_count

    # 存在子章节
    if pdf['child_chapters']:
      for child in pdf['child_chapters']:
        second_level_title = child['title']
        padf_path = os.path.join(dir_name, second_level_title + '.pdf')

        pdf_input = PdfFileReader(open(padf_path, 'rb'))
        # 获取 pdf 共用多少页
        page_count = pdf_input.getNumPages()
        for i in range(page_count):
            pdf_output.addPage(pdf_input.getPage(i))

        # 添加书签
        pdf_output.addBookmark(second_level_title, pagenum=pagenum, parent=parent_bookmark)
        # 增加页数
        pagenum += page_count

  # 合并
  pdf_output.write(open(outfn, 'wb'))

  # 删除所有章节文件
  shutil.rmtree(os.path.join(os.path.dirname(__file__), 'gen'))
