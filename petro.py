#! /bin/python3
import sys
import os
import re


header = '''\\documentclass[twocolumn,a4,twoside]{book}
\\usepackage{xeCJK} 
\\usepackage{amsmath, amsthm}
\\usepackage{listings,xcolor}
\\usepackage{geometry} 
\\usepackage{fontspec}
\\usepackage{graphicx}
\\usepackage{fancyhdr} 
\\setsansfont{Source Code Pro} 
\\setmonofont[Mapping={}]{Source Code Pro} 
\\geometry{left=2cm,right=1cm,top=2cm,bottom=1cm} 
\\setlength{\\columnsep}{30pt}


\\pagestyle{fancy}
\\fancyhead[RO,LE]{Page \\thepage}
\\fancyhead[LO,RE]{China University of Petroleum}
\\renewcommand{\\headrulewidth}{0.4pt} 
\\renewcommand{\\footrulewidth}{0.4pt}
\\cfoot{}

\\lstset{
	language    = c++,
	numbers     = left,
	numberstyle = \\tiny,
	breaklines  = true,
	captionpos  = b,
	tabsize     = 4,
	frame       = box,
	columns     = fullflexible,
	keywordstyle = \\bfseries,
	basicstyle   = \\small\\ttfamily,
	stringstyle  = \\color[RGB]{64,64,64}\\ttfamily,
	rulesepcolor = \\color{red!20!green!20!blue!20},
	showstringspaces = false,
}


\\title{\\CJKfamily{hei} {\\bfseries ACM模板}}
\\author{XORSUM}
\\renewcommand{\\today}{\\number\\year 年 \\number\\month 月 \\number\\day 日}

\\begin{document}\\small
	\\pagestyle{empty}
	\\begin{titlepage}
		\\maketitle
	\\end{titlepage}
	\\tableofcontents
	\\mainmatter
	\\pagestyle{fancy}'''

def read_file(path):
    with open(path,"r") as f:
        content = f.read()
        # print(content)
        return content
    return None


def write_file(path,content):
    head,tail = os.path.split(path)
    if not os.path.exists(head):
        os.mkdir(head)
    with open(path,"w") as f:
        f.write(content)
        return content
    return None



def extract_summary(content):
    pattern = re.compile('---\nindex: (.*)\ntitle: (.*)\n---',re.DOTALL)
    match = re.match(pattern, content)
    if match is not None:
        summary = {
            'index': match.group(1),
            'title': match.group(2),
        }
        return summary
    return None    

def extract_section(content):
    pattern = re.compile('---\nindex: (.*)\ntitle: (.*)\n---\n(.*)\n---\n(.*)',re.DOTALL)
    match = re.match(pattern, content)
    if match is not None:
        section = {
            'index': match.group(1),
            'title': match.group(2),
            'description': match.group(3),
            'code': match.group(4),
        }
        return section
    return None    



def scan_source(root_path="./src"):
    document = []
    for path in os.listdir(root_path):
        path = os.path.join(root_path,path)
        if os.path.isfile(path):
            continue
        summary = os.path.join(path,"summary.md")
        if not os.path.exists(summary):
            continue
        chapter = extract_summary(read_file(summary))
        if chapter is None:
            continue
        sections = []
        for file in os.listdir(path):
            if file == 'summary.md':
                continue
            file = os.path.join(path,file)
            section = extract_section(read_file(file))
            if section is not None:
                sections.append(section)
        sections.sort(key=lambda x:x['index'])
        chapter['sections']=sections
        document.append(chapter)
    document.sort(key=lambda x:x['index'])
    return document

def render_latex(document):
    latex = header
    for chapter in document:
        latex = latex + '\n    \\chapter{'+chapter['title']+'}\n'
        sections = chapter['sections']
        for section in sections:
            latex = latex + '        \\section{'+section['title']+'}\n'
            latex = latex + section['description'] + '\n'
            latex = latex + '        \\begin{lstlisting}\n'
            latex = latex + section['code']
            latex = latex + '        \\end{lstlisting}\n'
            print("Section  ",section['title'])
        latex = latex + '\n'
    latex = latex + '\\end{document}' # footer
    return latex

def create_chapter(name):
    path = os.path.join("src",name)
    if not os.path.exists(path):
        os.mkdir(path)
        content="---\nindex: 0\ntitle: "+name+"\n---\n"
        path = os.path.join(path,"summary.md")
        write_file(path,content)

def create_section(name):
    path = os.path.join("src",name+".md")
    if not os.path.exists(path):
        content="---\nindex: 0\ntitle: "+name+"\n---\n\ndescription\n\n---\n\ncode\n"
        write_file(path,content)

def show_help():
    help="""
nc <name> :  create new chapter
ns <name> :  create new section
g   :  generate latex file    
h   :  show help
"""
    print(help)

if __name__ == '__main__':

    try:
        command = sys.argv[1]
        if command == "g":
            document = scan_source()
            latex = render_latex(document)
            write_file("out/document.tex",latex)
        elif command == "nc":
            name = sys.argv[2]
            create_chapter(name)
        elif command == "ns":
            name = sys.argv[2]
            create_section(name)
        else:
            show_help()
    except Exception as e:
        repr(e)    
        show_help()


