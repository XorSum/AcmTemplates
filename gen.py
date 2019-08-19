import sys
import os
import re


def scan_files(root_path):
    file_pathes = []
    for i,j,k in os.walk(root_path):
        for l in k:
            path = os.path.join(i,l)
            # print(path)
            file_pathes.append(path)
    return file_pathes

def read_file(path):
    with open(path,"r") as f:
        content = f.read()
        # print(content)
        return content
    return None

def extract_data(content):
    pattern = re.compile('---\ntitle: (.*)\nchapter: (.*)\n---\n(.*)',re.DOTALL)
    match = re.match(pattern, content)
    if match is not None:
        # print(match.group(1))
        # print(match.group(2))
        # print(match.group(3))
        section = {
            'title': match.group(1),
            'chapter': match.group(2),
            'code': match.group(3),
        }
        return section
    return None    

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
	frame       = shadowbox,
	columns     = fullflexible,
	keywordstyle = \\bfseries,
	basicstyle   = \\small\\ttfamily,
	stringstyle  = \\color[RGB]{64,64,64}\\ttfamily,
	rulesepcolor = \\color{red!20!green!20!blue!20},
	showstringspaces = false,
}


\\title{\\CJKfamily{hei} {\\bfseries ACM模板}}
\\author{han777404}
\\renewcommand{\\today}{\\number\\year 年 \\number\\month 月 \\number\\day 日}

\\begin{document}\\small
	\\pagestyle{empty}
	\\begin{titlepage}
		\\maketitle
	\\end{titlepage}
	\\tableofcontents
	\\mainmatter
	\\pagestyle{fancy}'''

def render_latex(documents):
    with open("out.tex","w") as f:
        f.write(header)
        for chapter,sections in documents.items():
            f.write('\n    \\chapter{'+chapter+'}\n')
            print("Chapter  ",chapter)
            for section in sections:
                f.write('        \\section{'+section['title']+'}\n')
                f.write('        \\begin{lstlisting}\n')
                f.write(section['code'])
                f.write('        \\end{lstlisting}\n')
                print("Section  ",section['title'])
            f.write('\n')
            
        f.write('\\end{document}') # footer


if __name__ == '__main__':
    print("start")
    pathes = scan_files("./src")
    documents = {}
    for i in pathes:
        # print(i)
        content = read_file(i)
        if content is not None:
            section = extract_data(content)
            # print(section)
            if section is not None:
                l = documents.get(section['chapter'],[])
                l.append(section)
                documents[section['chapter']]=l
    # print(documents)
    render_latex(documents)


    print("end")