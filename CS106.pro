TEMPLATE = subdirs
SUBDIRS = Library Welcome NameHash CppLegs

# ordered forces subprojects to build sequentially, according to SUBDIRS
CONFIG += ordered
