      INTEGER*4 FUNCTION SETPAWC()
      INTEGER NPAWC
      PARAMETER (NPAWC = 1000000)
      INTEGER P
      COMMON /PAWC/ P(NPAWC)
      INTEGER IQUEST
      COMMON/QUEST/IQUEST(100)
      SETPAWC = NPAWC
      RETURN
      END
