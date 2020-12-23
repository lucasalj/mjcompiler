find_package(fmt CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)


add_library(mjc
            mjc_traits.cpp
            mjc_overloadset.cpp
            mjc_token.cpp mjc_assert.cpp
            mjc_loggingassertionhandler.cpp
            mjc_streamio.cpp
            mjc_reservedwords.cpp
            mjc_variant.cpp
            mjc_fileposition.cpp
            mjc_lexerprotocol.cpp
            mjc_lexer.cpp
            mjc_parser.cpp
            mjast_and.cpp
            mjast_arrayassign.cpp
            mjast_arraylength.cpp
            mjast_arraylookup.cpp
            mjast_assign.cpp
            mjast_block.cpp
            mjast_booleantype.cpp
            mjast_call.cpp
            mjast_classdecl.cpp
            mjast_classdeclextends.cpp
            mjast_classdecllist.cpp
            mjast_classdeclsimple.cpp
            mjast_exp.cpp
            mjast_explist.cpp
            mjast_false.cpp
            mjast_formal.cpp
            mjast_formallist.cpp
            mjast_identifier.cpp
            mjast_identifierexp.cpp
            mjast_identifiertype.cpp
            mjast_if.cpp
            mjast_intarraytype.cpp
            mjast_integerliteral.cpp
            mjast_integertype.cpp
            mjast_lessthan.cpp
            mjast_mainclass.cpp
            mjast_methoddecl.cpp
            mjast_methoddecllist.cpp
            mjast_minus.cpp
            mjast_newarray.cpp
            mjast_newobject.cpp
            mjast_not.cpp
            mjast_plus.cpp
            mjast_print.cpp
            mjast_program.cpp
            mjast_statement.cpp
            mjast_statementlist.cpp
            mjast_this.cpp
            mjast_times.cpp
            mjast_true.cpp
            mjast_type.cpp
            mjast_vardecl.cpp
            mjast_vardecllist.cpp
            mjast_while.cpp
            mjc_astdotprinter.cpp
            mjc_stringtable.cpp)

target_include_directories(mjc PUBLIC ./)
target_compile_features(mjc PRIVATE cxx_std_17)
target_link_libraries(mjc INTERFACE fmt::fmt fmt::fmt-header-only
                          PRIVATE magic_enum::magic_enum
                          PUBLIC debug_assert
                          PRIVATE absl::hash absl::algorithm absl::memory absl::hashtablez_sampler absl::container absl::any absl::base absl::bits absl::city absl::raw_hash_set)
