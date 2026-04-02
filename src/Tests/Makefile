
LIBRARY = ..\me_parse_tree.c ..\me_structure_blueprint.c
LIBRARY2 = ..\me_parse_tree_multichild.c ..\me_structure_blueprint.c ..\me_character_check.c
LIBRARY3 = ..\me_structure_blueprint.c
LIBRARY4 = ..\me_character_check.c

test_parse_tree:
	cl /utf-8 test_parse_tree.c $(LIBRARY) /Zi /Od

test_meptm:
	cl /utf-8 test_meptm.c $(LIBRARY2) /Zi /Od

test_me_structure_blueprint:
	cl /utf-8 test_me_structure_blueprint.c $(LIBRARY3) /Zi /Od

test_me_character_check: 
	cl /utf-8 test_me_character_check.c $(LIBRARY4) /Zi /Od

clean:
	del *.obj
	del *.exe
	del *.ilk
	del *.pdb