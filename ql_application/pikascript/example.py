def exec(file):
    f = open(file, 'r')
    script = f.read()
    eval(script)
    close(f)
