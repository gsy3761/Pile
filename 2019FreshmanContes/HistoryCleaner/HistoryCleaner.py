import json
# import urllib

def DealOldShit(str):
    print(str)
    return str

def latex(str=""):
    str = all(str)
    str = str.replace('>='," \\geq ")
    str = str.replace('<=', " \\leq ")
    str = str.replace('<', " < ")
    str = str.replace('>'," > ")
    str = str.replace('!='," \\neq ")
    str = str.replace('*'," \\cdot ")
    str = str.replace('~'," \\sim ")
    str = str.replace("&le;"," < ")
    str = str.replace("&hellip;", "\\cdots ")
    str = str.replace("&times;","\\times")
    str = str.strip()
    str = ' $'+ str+'$ '
    return str

def testData(str = ""):
    lines = str.split('\n')
    ret = ""
    for line in lines:
        line = line.strip()
        line = line.strip('>')
        line = line.strip()
        line = line.strip('`')

        if line:
            ret = ret+line+'\n'
    ret = '\n\n```\n'+ret+'```\n'
    return ret

def all(str = ""):
    lines = str.split('\n')
    ret = ""
    for line in lines:
        #line = line.replace('','')
        line = line.strip('>')
        line = line.strip()
        if '#' in line:
            line = line.replace(":","")
            line = line.replace("：","")
        line = line.replace("：",": ")
        ret = ret+line+'\n'
    #if ':'in ret and '：'in ret:
        #ret = ret.replace(":",'')
    ret = ret.replace('，'," , ")
    ret = ret.replace('。',". ")
    ret = ret.replace('？'," ? ")
    ret = ret.replace("；",";")
    ret = ret.replace('（'," ( ")
    ret = ret.replace('）'," ) ")
    ret = ret.replace("&rdquo;", "`")
    ret = ret.replace("..."," $\\dots$ ")
    ret = ret.replace("/problem/submit?tw=","/problem/")
    return ret

def main():
    # inPutFile = open("./Data/problems.json","r",encoding = "UTF-8")
    # inPutData = inPutFile.read()
    # decodedData = json.loads(inPutData)
    # for p in decodedData:
    #     p["content"] = DealOldShit(p["content"])
    inputFile = open("./temp.txt",'r',encoding = "UTF-8")
    inputStr = inputFile.read()
    if '\n' in inputStr:
        if not '#' in inputStr:
            inputStr = testData(inputStr)
        else:
            inputStr = all(inputStr)
    else:
        inputStr = latex(inputStr)
    inputFile.close()
    inputFile = open("./temp.txt",'w',encoding = "UTF-8")
    inputFile.write(inputStr)
    return 


if __name__ == "__main__":
    main()