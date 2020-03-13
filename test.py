def test():
    sorted_sub = [1,4,5,5, 5, 5, 7,9,11,15,17]
    sorted_full = [4, 4, 4, 4, 4,5,8,17]

    full_ix = 0
    sub_ix = 0

    while full_ix < len(sorted_full) and sub_ix < len(sorted_sub):
        curr_full = sorted_full[full_ix]
        curr_sub = sorted_sub[sub_ix]
        if curr_full == curr_sub:
            print('Common id ' + str(curr_full) + ' at index ' + str(full_ix))
            full_ix +=1
            sub_ix +=1
            continue
        if curr_full < curr_sub:
            full_ix +=1
        else:
            sub_ix+=1


test()