# SQL definition for procedural languages
# PostgreSQL Version: 8.0
# CAUTION: Do not modify this file unless you know what
#          you are doing.

[-- object: ] @{name} [ | type: ] @{sql-object} [ -- ] $br

[CREATE ] %if @{trusted} %then [TRUSTED ] %end
[ LANGUAGE ] @{name}

#%if @{handler} %then
 $br $tb [HANDLER ] @{handler}
# %end

%if @{validator} %then
 $br $tb [VALIDATOR ] @{validator}
%end
; $br

%if @{owner} %then @{owner} %end
%if @{comment} %then @{comment} %end
