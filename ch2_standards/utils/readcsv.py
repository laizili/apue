def csv_reader(pathname: str, sep="\t"):
    with open(pathname) as fd:
        rows = []
        for raw_r in fd:
            raw_r = raw_r.strip()
            tmpr = raw_r.split(sep=sep)
            row = []
            for item in tmpr:
                if item != "":
                    row.append(item)
            rows.append(row)
        return rows
