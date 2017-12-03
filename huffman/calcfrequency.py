#!/usr/bin/env python3
# -*- coding:utf-8 -*-

def readForFile(filename):
    """read all character form filename"""
    with open(filename,'r') as f:
        lines = f.readlines
    
