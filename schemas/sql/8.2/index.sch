# SQL definition for indexes
# PostgreSQL Version: 8.2
# CAUTION: Do not modify this file unless you know what
#          you are doing.

[-- object: ] @{name} [ | type: ] @{sql-object} [ -- ] $br

[CREATE ] %if @{unique} %then [UNIQUE ] %end [INDEX ]

%if @{concurrent} %then
 [ CONCURRENTLY ]
%end

@{name} [ ON ] @{table} $br

%if @{index-type} %then
 $tb [USING ] @{index-type} $br
%end

$tb ( @{elements} ) $br

%if @{expression} %then
  $tb (@{expression}) $sp 
%end

$tb [WITH (FILLFACTOR = ] @{factor} [)] $br

%if @{tablespace} %then
 $tb [TABLESPACE ] @{tablespace} $br
%end

%if @{condition} %then
 $tb [WHERE (] @{condition} [)] $br
%end
;$br

%if @{comment} %then  @{comment} %end
