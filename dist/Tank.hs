#!/usr/bin/env runhaskell
{-# LANGUAGE TemplateHaskell #-}
{-# LANGUAGE LambdaCase #-}

module Main where
import System.Directory
import System.Process
import System.Exit
import System.IO
import System.FilePath.Manip
import Data.FileEmbed
import Data.List.Utils
import qualified Data.ByteString.Char8 as BS

main :: IO ()
main = do
    projectName <- getStr "What is the name of your project? "
    makeDirectories projectName
    installTank projectName
    initProject projectName

exit :: String -> String -> IO ()
exit projectName err = do
    hPutStrLn stderr err
    setCurrentDirectory ".."
    removeDirectoryRecursive projectName
    exitFailure

getStr :: String -> IO String
getStr putstr = do
    putStrLn putstr 
    getLine

makeDirectories :: String -> IO ()
makeDirectories projectName = do
    createDirectory projectName 
    setCurrentDirectory projectName
    createDirectory "src"
    createDirectory "assets"
    createDirectory "build"

installTank :: String -> IO ()
installTank projectName = findExecutable "git" >>= \case
    -- Git not found
    Nothing -> exit projectName "Cannot find git" 
    -- Git found
    _ -> do system "git init"
            system "git submodule add git@github.com:Gazok/Tank.git"
            system "git submodule init"
            system "git submodule update"
            return ()

fileReplace :: FilePath -> String -> String -> IO()
fileReplace s1 s2 = modifyInPlace (replace s1 s2)

initProject :: String -> IO ()
initProject projectName = do
    mapM_ (uncurry BS.writeFile) $(embedDir "templates")

    fileReplace projectName "CMakeLists.txt" "<project_name>"

    _ <- system "git commit -m \"Initial commit.\" -a"
    return ()
