#pragma once

enum class Type {
    array('N'),
    var('V'),
    nul('V'),
    gettable('#'),
    fn('F'),
    mop('M'),
    dop('D'),
    set('←'),
    dim('@');

    char chr;

    Type(char chr) {
        this.chr = chr;
    }
};